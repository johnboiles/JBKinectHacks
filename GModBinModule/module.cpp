/*
 * Copyright (c) 2010 John Boiles <johnaboiles@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Module.h"
#include "GMLuaModule.h"

// Module definition
GMOD_MODULE( Init, Shutdown );

// Globals
ILuaInterface* g_Lua;

LUA_FUNCTION( PrintSomething )
{
	g_Lua->Msg( "Hello, there!\n" );
	return 0;
}

// Initialization
int Init( lua_State *L )
{
	g_Lua = Lua();
	g_Lua->SetGlobal( "PrintSomething", PrintSomething );
	g_Lua->Msg( "New Module Loaded!\n" );
	return 0;
}

// Shutdown
int Shutdown( lua_State *L )
{
	g_Lua->Msg("Module Unloaded!\n");
	return 0;
}