About
=====

Example OSX (and possibly Win32 w/ Cygwin) compatible binary module project
for Garry's mod

Installation
============

Update Makefile to contain your steam username

<pre>
$ make install
</pre>

Usage
=====

In Garry's mod, start a game and from the console type
<pre>
lua_run require("module")
lua_run PrintSomething()
</pre>