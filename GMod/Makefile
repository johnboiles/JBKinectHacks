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

# Change this line to your steam username, or build using (at least on osx)
# make install STEAM_USERNAME=anotheruser
STEAM_USERNAME = jaboiles

INSTALL_PATH = ~/Library/Application\ Support/Steam/SteamApps/$(STEAM_USERNAME)/garrysmod/garrysmod/lua

install:
	mkdir -p $(INSTALL_PATH)/entities
	cp -r Entities/* $(INSTALL_PATH)/entities/
	cp Scripts/*.lua $(INSTALL_PATH)/
	cp BinaryModules/*.dll $(INSTALL_PATH)/includes/modules/
