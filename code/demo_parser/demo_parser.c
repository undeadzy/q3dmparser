#include <stdio.h>
#include "demo_public.h"
#include "../sys/sys_loadlib.h"

int
main(int argc, const char *argv[])
{
	demoPlugin_t *dem;

	if (argc != 2) {
		fprintf(stderr, "Usage: <demo file>\n");
		exit(EXIT_FAILURE);
	}

	demo_init_urt_411_plugin();

	if (! CL_ParseDemo(argv[1], 0)) {
		fprintf(stderr, "Error operating on \"%s\"\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// Load a DLL
	if ((dem = demoPluginDynamicLoad("demo_dummy_" ARCH_STRING DLL_EXT)) == NULL) {
		debug_print("Failed to load the dummy plugin");
		exit(EXIT_FAILURE);
	}

	printPluginSummary(dem);

	// Make sure we can run it several times.  The registry should still be in tact.
	//
	// It should now run with both UrT and the dummy plugin for every callback.

	if (! CL_ParseDemo(argv[1], 0)) {
		fprintf(stderr, "Error operating on \"%s\"\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	demoPluginFreeRegistry();

	return 1;
}

