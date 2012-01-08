#ifndef DEMO_PARSER_PUBLIC_H
#define DEMO_PARSER_PUBLIC_H 1

/* This is based on libpurple from pidgin. */
/* purple
 *
 * Purple is the legal property of its developers, whose names are too numerous
 * to list here.  Please refer to the COPYRIGHT file distributed with this
 * source distribution.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 */

#include "../client/client.h"
#include "../sys/sys_loadlib.h"

#define DEMO_PLUGIN_MAGIC 0xdeadbeef
#define DEMO_PLUGIN_MAJOR 0
#define DEMO_PLUGIN_MINOR 1

struct demoPlugin_s;

typedef struct {
	// Mirror some of libpurple's plugin setup
	const unsigned int magic;
	const unsigned int major_version;
	const unsigned int minor_version;
	const char *name;
	const char *version;
	const char *author;
	const char *description;
	const char *url;
	const char *license;  // Must be GPLv2 compatible

	const char *path;

	qboolean (*load)(struct demoPlugin_s *plugin);
	qboolean (*unload)(struct demoPlugin_s *plugin);
	qboolean (*destroy)(struct demoPlugin_s *plugin);

	void (*beforeDemo)(struct demoPlugin_s *plugin);
	void (*afterDemo)(struct demoPlugin_s *plugin);

	/* Note: This skips nop and download since they are not in demos */

	void (*commandString)(struct demoPlugin_s *plugin, const char *s);
	void (*preGamestate)(struct demoPlugin_s *plugin);
	void (*postGamestate)(struct demoPlugin_s *plugin);
	void (*preSnapshot)(struct demoPlugin_s *plugin, clSnapshot_t *new_snap);
	void (*postSnapshot)(struct demoPlugin_s *plugin);
	void (*preVoip)(struct demoPlugin_s *plugin);
	void (*postVoip)(struct demoPlugin_s *plugin);
} demoPluginInfo_t;

typedef struct demoPlugin_s {
	qboolean loaded;
	void     *handle;
	const char *path;
	demoPluginInfo_t *info;

	/* Three main globals from cl_main.c that can be useful when viewing demos */
	clientActive_t *cl;
	clientConnection_t *clc;
	clientStatic_t *cls;

	void     *data; /* Plugin-specific data */
} demoPlugin_t;

typedef struct demoPluginRegistry_s {
	demoPlugin_t *plugin;
	struct demoPluginRegistry_s *next;
} demoPluginRegistry_t;

demoPlugin_t *newDemoPlugin(const char *path);
qboolean isCorrectVersion(demoPlugin_t *plugin);
qboolean isValidDemoPlugin(demoPlugin_t *plugin);
qboolean printPluginSummary(demoPlugin_t *plugin);
qboolean demoPluginLoad(demoPlugin_t *plugin);
qboolean demoPluginRegister(demoPlugin_t *plugin);
void demoPluginNewRegistry(void);
void demoPluginFreeRegistry(void);

typedef qboolean (*demoPluginInit)(demoPlugin_t *plugin);

demoPlugin_t *demoPluginDynamicLoad(const char *path);

/* This has a simple registry so we don't mirror libpurple yet. */

#ifdef DEMO_STATIC_PLUGIN
#define _FUNC_NAME(x) demo_init_##x##_plugin
#define DEMO_INIT_PLUGIN(pluginName, initFunc, pluginInfo) \
	qboolean _FUNC_NAME(pluginName)(void);			 \
	qboolean _FUNC_NAME(pluginName)(void) { \
		demoPlugin_t *plugin = newDemoPlugin(NULL); \
		plugin->info = &(pluginInfo); \
		initFunc((plugin)); \
		return demoPluginRegister(plugin);	\
	}
#else
#define DEMO_INIT_PLUGIN(pluginName, initFunc, pluginInfo) \
	QDECL demoPlugin_t *demo_plugin_init(demoPlugin_t *plugin);	\
	QDECL demoPlugin_t *demo_plugin_init(demoPlugin_t *plugin) { \
		plugin->info = &(pluginInfo); \
		initFunc((plugin)); \
		return plugin; \
	}
#endif

extern demoPluginRegistry_t *demoPluginRegistry;

qboolean demo_init_urt_411_plugin(void);

#endif /* DEMO_PARSER_PUBLIC_H */
