TODO
====

This should generate stats like the name implies.  It's a matter of filling in
the callback functions.

Portability:
------------

* Replace <err.h> calls
* Test on platforms other than Linux.
* Test cross compiling

Functionality:
--------------

* Add support for VoIP
  - Need an example demo with VoIP data
* Add support for loading in shared libraries to add support for games
    - Stats for quake3, OA, Tremulous, WoP, UrT, etc
* Use getopt for demo_parser.c
* Add support for recursively finding *.dm_68 files and producing output based
  on it.
* Replace the way the plugins are registered and utilized
   - No good way to organize them or unload on demand other than the whole thing
   - Current implementation is crude compared to libpurple

Concerns:
---------

* Is there any global data that is not being reset upon a call to CL_ParseDemo?
* Is anything missed such that this doesn't act like a client minus
  rendering/sound/etc?

Documentation:
--------------

  Examples of common operations that people will want to do with cl, clc, cls
   - Any other globals that should be included?
   - Example of pitfalls as well since we don't have the QVM state

