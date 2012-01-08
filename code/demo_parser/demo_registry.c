#include "demo_public.h"

/* This is an ugly array of plugins as a global so it cannot be called as libpurple does.
   Replace me.
 */
demoPluginRegistry_t *demoPluginRegistry;

qboolean
demoPluginRegister(demoPlugin_t *plugin)
{
	demoPluginRegistry_t *current;

	if (! isCorrectVersion(plugin)) {
		fprintf(stderr, "Invalid version of plugin\n");
		return qfalse;
	}

	/* Give the plugin a pointer to useful client side info */
	plugin->cl = &cl;
	plugin->clc = &clc;
	plugin->cls = &cls;

	if (demoPluginRegistry == NULL) {
		demoPluginNewRegistry();
		demoPluginRegistry->plugin = plugin;
		return qtrue;
	}

	for (current = demoPluginRegistry; current != NULL; current = current->next) {
		if (current->next == NULL) {
			demoPluginRegistry_t *new_entry;

			if ((new_entry = malloc(sizeof(demoPluginRegistry_t))) == NULL) {
				fprintf(stderr, "Failed to alloc\n");
				exit(EXIT_FAILURE);
			}
			new_entry->plugin = plugin;
			new_entry->next   = NULL;

			current->next = new_entry;
			break;
		}
	}

	return qfalse;
}

demoPlugin_t *
newDemoPlugin(const char *path)
{
	demoPlugin_t *plugin;

	if ((plugin = calloc(sizeof(demoPlugin_t), 1)) == NULL) {
		fprintf(stderr, "Failed to alloc\n");
		exit(EXIT_FAILURE);
	}

	return plugin;
}

void
freeDemoPlugin(demoPlugin_t *plugin)
{
	if (plugin == NULL) {
		return;
	}

	if (plugin->info != NULL && plugin->info->unload != NULL) {
		plugin->info->unload(plugin);
	}

	// Not a dynamic library
	if (! plugin->loaded) {
		if (plugin->handle != NULL) {
			fprintf(stderr, "Error: Should not have a handle with a static library (%s:%d)\n", __FILE__, __LINE__);
		}
		free(plugin);
		return;
	}

	free((char *)plugin->info->path);

	if (plugin->handle != NULL) {
		if (! plugin->loaded) {
			fprintf(stderr, "Should have previously loaded it (%s:%d)\n", __FILE__, __LINE__);
		}
		Sys_UnloadDll(plugin->handle);
	}

	free(plugin);
}


void
demoPluginNewRegistry(void) {
	if (demoPluginRegistry != NULL) {
		demoPluginFreeRegistry();
	}

	if ((demoPluginRegistry = malloc(sizeof(demoPluginRegistry_t))) == NULL) {
		fprintf(stderr, "Failed to alloc\n");
		exit(EXIT_FAILURE);
	}

	demoPluginRegistry->plugin = NULL;
	demoPluginRegistry->next   = NULL;
}

void
demoPluginFreeRegistry(void) {
	demoPluginRegistry_t *current;

	for (current = demoPluginRegistry; current != NULL; current = current->next) {
		demoPluginRegistry_t *save;
		save = current->next;

		freeDemoPlugin(current->plugin);
		free(current);

		current = save;

		if (current == NULL) {
			break;
		}
	}

	demoPluginRegistry = NULL;
}

qboolean
demoPluginLoad(demoPlugin_t *plugin)
{
	if (plugin == NULL) {
		return qfalse;
	}

	if (plugin->info != NULL && plugin->info->load != NULL) {
		if (! plugin->info->load(plugin)) {
			return qfalse;
		}
	}

	if ((plugin->handle = Sys_LoadDll(plugin->info->path, qfalse)) == NULL) {
		return qfalse;
        }

	plugin->loaded = qtrue;

	return qtrue;
}

qboolean
isValidPlugin(demoPlugin_t *plugin)
{
	if (plugin == NULL) {
		return qfalse;
	}

	if (! isCorrectVersion(plugin)) {
		return qfalse;
	}

	return qtrue;
}

qboolean
isCorrectVersion(demoPlugin_t *plugin)
{
	if (plugin->info->magic != DEMO_PLUGIN_MAGIC) {
		fprintf(stderr, "Invalid magic number.  Found %d and expected %d\n",
			plugin->info->magic, DEMO_PLUGIN_MAGIC);
		return qfalse;
	}

	if (plugin->info->major_version < DEMO_PLUGIN_MAJOR
	    || plugin->info->minor_version < DEMO_PLUGIN_MINOR) {
		fprintf(stderr, "ABI version mismatch %d.%d and need %d.%d\n",
			plugin->info->major_version, plugin->info->minor_version,
			DEMO_PLUGIN_MAJOR, DEMO_PLUGIN_MINOR);
		return qfalse;
	}

	return qtrue;
}

qboolean
printPluginSummary(demoPlugin_t *plugin)
{
	if (! isValidPlugin(plugin)) {
		return qfalse;
	}

	if (plugin->info == NULL) {
		return qfalse;
	}

	printf("Name: %s\n"
	       "Version: %s\n"
	       "Author: %s\n"
	       "Description: %s\n"
	       "URL: %s\n"
	       "License (must be GPLv2 compatible): %s\n",
	       (plugin->info->name == NULL        ? "" : plugin->info->name),
	       (plugin->info->version == NULL     ? "" : plugin->info->version),
	       (plugin->info->author == NULL      ? "" : plugin->info->author),
	       (plugin->info->description == NULL ? "" : plugin->info->description),
	       (plugin->info->url == NULL         ? "" : plugin->info->url),
	       (plugin->info->license == NULL     ? "" : plugin->info->license));

	return qtrue;
}

demoPlugin_t *
demoPluginDynamicLoad(const char *path)
{
	demoPlugin_t *plugin;
	demoPluginInit initFunc;

	if ((plugin = newDemoPlugin(path)) == NULL) {
		debug_print("Failed to load the library");
		return NULL;
	}

	if ((plugin->handle = Sys_LoadDll(path, qfalse)) == NULL) {
		debug_print(Sys_LibraryError());
		return NULL;
        }

	if ((initFunc = Sys_LoadFunction(plugin->handle, "demo_plugin_init")) == NULL) {
		debug_print(Sys_LibraryError());
		if (! Sys_UnloadLibrary(plugin->handle)) {
			debug_print(Sys_LibraryError());
		}
		return NULL;
	}

	if (! initFunc(plugin)) {
		debug_print("Failed to initialize the plugin");
		if (! Sys_UnloadLibrary(plugin->handle)) {
			debug_print(Sys_LibraryError());
		}
		return NULL;
	}

	demoPluginRegister(plugin);

	plugin->info->path = strdup(path);

	return plugin;
}
