About
=====

Lua bindings to zeromq2 for use in Garry's mod. THESE DON'T CURRENTLY WORK.
Based on the official lua-zmq bindings available at:
https://github.com/iamaleksey/lua-zmq

If you can make these work, please do. It would be awesome. Currently they build,
but they crash gmod. It looks like the lua_State pointer might be invalid.

Requirements
============

Requires a 32-bit version of lua as well as a 32-bit version of zmq to be available.

You can build lua as a 32-bit library using macports

	sudo port install lua +universal

It is however a bit harder to set up zmq as universal. Included in misc/build_universal.sh
is a helper script to create a universal build from a zeromq2 source checkout. You must
edit that script to contain the path of your zeromq install.

	/path/to/build_universal.sh
	cd /path/to/zeromq2
	sudo cp bin_universal/* /opt/local/lib/ # (or other suitable lib location)

Installation
============

<pre>
$ make install
</pre>

API
===

See [API.md](http://github.com/iamaleksey/lua-zmq/blob/master/API.md) and
[ØMQ docs](http://www.zeromq.org/area:docs-v20).
