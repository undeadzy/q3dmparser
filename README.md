Q3DMParse 0.0.1
===============

Quake 3 demo parser using callbacks.  It is built on ioquake3 without client
rendering or QVM execution.

Unlike most other tools, this does not operate on a log file.  As such, it's
not subject to any abnormalities associated with high (>= 3) timescales when
producing logs.  It takes about a second to run on my machine for a 25 minute
recorded demo.

Therefore, if the mod is spitting out special strings to the screen that you
want to get, you would have to replicate that code in here.

For instance in UrT, you won't get the death messages about what weapon people
were killed with.  However, you have all of the state information needed to
recreate that message.

             | QVM messages | Fast | Client state   | Easily maintainable
-------------+--------------+------+----------------+--------------------
log parsers  |   Yes        | No   | No  (partial)  | Maybe (per game)
old dm_68    |   No         | Yes  | Yes (partial?) | No (GPL + SDK??)
Q3DMParse    |   No         | Yes  | Yes            | Yes (uses ioquake3)

The old dm_68 parser is here: http://skuller-vidnoe.narod.ru/  I didn't use
any of this code.  Q3DMParse is a completely separate project.

By fast, it's referring to the total time from receiving a *.dm_68 file to
getting output.  While log parsers are fast, there is considerable time needed
to generate the input.  It can also be problematic running older mod versions
such as UrT < 4 which was not standalone.

Alternatives
------------

If you need the quake3 mod/standalone messages from the QVM code, you should
check out q3dmplayer which is a full ioquake3 client without sound or rendering
to improve the speed.  For the same 25 minute match, it takes about 30 seconds
to run through the q3dmplayer rather than parser.  It throws all of the
output into a sqlite3 database since Com_Printf is unreliable at high
timescales.

HOWTO
-----

Add a callback library for your game type.  If you want to access methods from
ioquake3, you will need to include that code in the library.  Watch out for
any globals that they refer to.  The callback definition includes pointers to
cl, clc and cls.  These aren't as useful as you would hope though.  The QVM
code generates the messages and if you want the actual messages, you will
want to try q3dmplayer rather than this project.

See code/demo_parser/demo_dummy.c for an example

