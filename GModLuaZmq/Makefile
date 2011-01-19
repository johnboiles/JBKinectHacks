# Copyright (c) 2010 Aleksey Yeschenko <aleksey@yeschenko.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

CC = g++
CFLAGS = `pkg-config lua --cflags` -fPIC -O3 -Wall -arch i386 -Iinclude
# We probably need to link against Gmod's lua_shared.dylib if we hope to have access
# to all the c functions.
LFLAGS = -shared -arch i386 `pkg-config --libs --cflags lua` -lzmq
STEAM_USERNAME = jaboiles
INSTALL_PATH = ~/Library/Application\ Support/Steam/SteamApps/$(STEAM_USERNAME)/garrysmod/garrysmod/lua/includes/modules

all: gm_zmq_osx.dll


gm_zmq.lo: gm_zmq.cpp
	$(CC) -o gm_zmq.lo -c $(CFLAGS) gm_zmq.cpp


gm_zmq_osx.dll: gm_zmq.lo
	$(CC) -o gm_zmq_osx.dll $(LFLAGS) gm_zmq.lo


install: gm_zmq_osx.dll
	install -d $(INSTALL_PATH)
	install gm_zmq_osx.dll $(INSTALL_PATH)/gm_zmq_osx.dll


clean:
	rm -f gm_zmq_osx.dll gm_zmq.lo
