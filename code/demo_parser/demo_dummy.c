#include "demo_public.h"

/* Loading related */
static qboolean plugin_load(demoPlugin_t *plugin) {
	fprintf(stderr, "In plugin load (%s:%d [build: %s %s])\n", __FILE__, __LINE__, __DATE__, __TIME__);
	return qtrue;
}

static qboolean plugin_unload(demoPlugin_t *plugin) {
	fprintf(stderr, "In plugin unload (%s:%d [build: %s %s])\n", __FILE__, __LINE__, __DATE__, __TIME__);
	return qtrue;
}

static qboolean plugin_destroy(demoPlugin_t *plugin) {
	fprintf(stderr, "In plugin destroy (%s:%d [build: %s %s])\n", __FILE__, __LINE__, __DATE__, __TIME__);
	return qtrue;
}

/* Demo related */

static void commandString(demoPlugin_t *plugin, const char *s)
{
	fprintf(stderr, "In command string (%s:%d [build: %s %s])\n", __FILE__, __LINE__, __DATE__, __TIME__);
}

static void preGamestate(demoPlugin_t *plugin)
{
	fprintf(stderr, "In pre-game state (%s:%d [build: %s %s])\n", __FILE__, __LINE__, __DATE__, __TIME__);
}

static void postGamestate(demoPlugin_t *plugin)
{
	fprintf(stderr, "In post-game state (%s:%d [build: %s %s])\n", __FILE__, __LINE__, __DATE__, __TIME__);
}

static void preSnapshot(demoPlugin_t *plugin, clSnapshot_t *newsnap)
{
	fprintf(stderr, "In pre-snapshot (%s:%d [build: %s %s])\n", __FILE__, __LINE__, __DATE__, __TIME__);
}

static void postSnapshot(demoPlugin_t *plugin)
{
	fprintf(stderr, "In post-snapshot (%s:%d [build: %s %s])\n", __FILE__, __LINE__, __DATE__, __TIME__);
}

static void preVoip(demoPlugin_t *plugin)
{
	fprintf(stderr, "In pre-voip (%s:%d [build: %s %s])\n", __FILE__, __LINE__, __DATE__, __TIME__);
}

static void postVoip(demoPlugin_t *plugin)
{
	fprintf(stderr, "In post-voip (%s:%d [build: %s %s])\n", __FILE__, __LINE__, __DATE__, __TIME__);
}

/* Required structure to tell the caller about this plugin */

static demoPluginInfo_t info = {
	DEMO_PLUGIN_MAGIC,			/* Plugin standard magic */
	DEMO_PLUGIN_MAJOR,			/* Plugin standard major_version */
	DEMO_PLUGIN_MINOR,			/* Plugin standard minor_version */

	"Dummy",				/* Plugin name */
	"0.0.1",				/* Plugin version */
	"undeadzy",				/* Plugin author */
	"Dummy plugin which is very verbose",	/* Plugin description */
	"https://github.com/undeadzy/ioquake3_mirror/tree/t/q3dmparser", /* Plugin URL */
	"GPLv2+",				/* Plugin license (must be GPLv2 compatible) */
	"demo_dummy_" ARCH_STRING DLL_EXT,	/* Plugin path for DLL */

	/* Any of the rest may be NULL if you want to skip them */

	&plugin_load,				/* Plugin load callback */
	&plugin_unload,				/* Plugin unload callback */
	&plugin_destroy,			/* Plugin destroy callback */

	NULL,					/* Plugin beforeDemo callback */
	NULL,					/* Plugin afterDemo callback */

	&commandString,				/* Plugin commandString callback */
	&preGamestate,				/* Plugin preGamestate callback */
	&postGamestate,				/* Plugin postGamestate callback */
	&preSnapshot,				/* Plugin preSnapshot callback */
	&postSnapshot,				/* Plugin postSnapshot callback */
	&preVoip,				/* Plugin preVoip callback */
	&postVoip				/* Plugin postVoip callback */
};

/* Special initialization.  For normal load/unload, use the demoPluginInfo_t methods */
static void
init_plugin(demoPlugin_t *plugin)
{
	debug_print("Initializing dummy");
}

DEMO_INIT_PLUGIN(dummy, init_plugin, info);
