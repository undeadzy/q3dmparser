#include "demo_public.h"

/* This doesn't do anything except show you the bare minimum */

static demoPluginInfo_t info = {
	DEMO_PLUGIN_MAGIC,			/* Plugin standard magic */
	DEMO_PLUGIN_MAJOR,			/* Plugin standard major_version */
	DEMO_PLUGIN_MINOR,			/* Plugin standard minor_version */

	"Silent",				/* Plugin name */
	"0.0.1",				/* Plugin version */
	"undeadzy",				/* Plugin author */
	"Silent plugin that doesn't do anything", /* Plugin description */
	"https://github.com/undeadzy/ioquake3_mirror/tree/t/q3dmparser",	/* Plugin URL */
	"GPLv2+",				/* Plugin license (must be GPLv2 compatible) */
	"demo_silent_" ARCH_STRING DLL_EXT,	/* Plugin path for DLL */

	/* Any of the rest may be NULL if you want to skip them */

	NULL,					/* Plugin load callback */
	NULL,					/* Plugin unload callback */
	NULL,					/* Plugin destroy callback */

	NULL,					/* Plugin beforeDemo callback */
	NULL,					/* Plugin afterDemo callback */

	NULL,					/* Plugin commandString callback */
	NULL,					/* Plugin preGamestate callback */
	NULL,					/* Plugin postGamestate callback */
	NULL,					/* Plugin preSnapshot callback */
	NULL,					/* Plugin postSnapshot callback */
	NULL,					/* Plugin preVoip callback */
	NULL,					/* Plugin postVoip callback */
};

static void
init_func(demoPlugin_t *plugin)
{
}

DEMO_INIT_PLUGIN(silent, init_func, info);
