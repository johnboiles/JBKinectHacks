# Copyright (c) 2011 John Boiles <johnaboiles@gmail.com>
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
# add -O3 for optimizations
CFLAGS = -fPIC -Wall -arch i386 -Iinclude
LFLAGS = -shared -arch i386
STEAM_USERNAME = jaboiles
INSTALL_PATH = ~/Library/Application\ Support/Steam/SteamApps/$(STEAM_USERNAME)/garrysmod/garrysmod/lua/includes/modules


all: gm_module_osx.dll


module.lo: module.cpp
	$(CC) -o module.lo -c $(CFLAGS) module.cpp


gm_module_osx.dll: module.lo
	$(CC) -o gm_module_osx.dll $(LFLAGS) module.lo


install: gm_module_osx.dll
	install -d $(INSTALL_PATH)
	install gm_module_osx.dll $(INSTALL_PATH)/gm_module_osx.dll


clean:
	rm -f gm_module_osx.dll module.lo
