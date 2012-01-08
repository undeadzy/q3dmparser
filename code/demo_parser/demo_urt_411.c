#include <stdio.h>
#include "demo_public.h"

#ifndef DEMO_STATIC_PLUGIN
#  error "This may use globals so it needs to be static"
#endif

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

static void commandString(demoPlugin_t *plugin, const char *s) {
	fprintf(stderr, "UrT 4.x %s\n", s);
	// fprintf(stderr, "First player should be at %d but is at %d = %s\n", CS_PLAYERS, CS_PLAYERS + 4, Info_ValueForKey( plugin->cl->gameState.stringData + plugin->cl->gameState.stringOffsets[ CS_PLAYERS + 4 ], "n" ));
}

#if 0
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
	fprintf(stderr, "In pre-snapshot (%s:%d [build: %s %s])\n", __FILE__, __LINE__, __DATE__, __TIME__);
}

static void preVoip(demoPlugin_t *plugin)
{
	fprintf(stderr, "In pre-voip (%s:%d [build: %s %s])\n", __FILE__, __LINE__, __DATE__, __TIME__);
}

static void postVoip(demoPlugin_t *plugin)
{
	fprintf(stderr, "In post-voip (%s:%d [build: %s %s])\n", __FILE__, __LINE__, __DATE__, __TIME__);
}
#endif

/* Required structure to tell the caller about this plugin */

static demoPluginInfo_t info = {
	DEMO_PLUGIN_MAGIC,			/* Plugin standard magic */
	DEMO_PLUGIN_MAJOR,			/* Plugin standard major_version */
	DEMO_PLUGIN_MINOR,			/* Plugin standard minor_version */

	"UrT 4.1.1",				/* Plugin name */
	"0.0.1",				/* Plugin version */
	"undeadzy",				/* Plugin author */
	"Urban Terror 4.1.1 stats plugin",	/* Plugin description */
	"https://github.com/undeadzy/ioquake3_mirror/tree/t/q3dmparser", /* Plugin URL */
	"GPLv2+",				/* Plugin license (must be GPLv2 compatible) */
	NULL, /* Uses globals so be static */ 	/* Plugin path for DLL */

	/* Any of the rest may be NULL if you want to skip them */

	&plugin_load,				/* Plugin load callback */
	&plugin_unload,				/* Plugin unload callback */
	&plugin_destroy,			/* Plugin destroy callback */

	NULL,					/* Plugin beforeDemo callback */
	NULL,					/* Plugin afterDemo callback */

	&commandString,				/* Plugin commandString callback */
	NULL,					/* Plugin preGamestate callback */
	NULL,					/* Plugin postGamestate callback */
	NULL,					/* Plugin preSnapshot callback */
	NULL,					/* Plugin postSnapshot callback */
	NULL,					/* Plugin preVoip callback */
	NULL,					/* Plugin postVoip callback */
};

/* Special initialization.  For normal load/unload, use the demoPluginInfo_t methods */
static void
init_plugin(demoPlugin_t *plugin)
{
}

DEMO_INIT_PLUGIN(urt_411, init_plugin, info);
