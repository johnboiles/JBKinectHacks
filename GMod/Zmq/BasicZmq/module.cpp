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
#include <zmq.hpp>

// Module definition
GMOD_MODULE( Init, Shutdown );

LUA_FUNCTION( PrintSomething )
{
	g_Lua->Msg( "Hello, there!\n" );
	return 0;
}

LUA_FUNCTION( ZmqVersion )
{
	int major, minor, patch;
	zmq_version(&major, &minor, &patch);
	char string[100];
	sprintf(string, "major %d minor %d patch %d\n", major, minor, patch);
	g_Lua->Msg( string );
	return 0;
}

	// May be able to increase the number of threads here

zmq::context_t context(5);
zmq::socket_t socket(context, ZMQ_REP);

LUA_FUNCTION( ZmqInit )
{
	errno = zmq_errno();
	if (errno) {
		g_Lua->Msg( "Error: %d %s\n", errno,  zmq_strerror(errno));
	}
	// Receiving data using connect seems to hang and never do anything
	//socket.connect("tcp://127.0.0.1:5555");
	// Bind only seems to receive data when polling
	socket.bind("tcp://127.0.0.1:5555");
}

LUA_FUNCTION( ZmqReceive )
{
	try {
		g_Lua->Msg( "Receiving Data!\n" );
		zmq::message_t receivedMessage(100);
		zmq_pollitem_t items [1];
		items[0].socket = &socket;
		items[0].events = ZMQ_POLLIN;
		// Setting the last param of poll to -1 causes it block while waiting for data,
		// Nonblocking never seems to get data though
		//if (zmq::poll(items, 1, -1)) {
		//	socket.recv(&receivedMessage, 0);
			// I'm not sure why the NOBLOCK flag never seems to get data
			socket.recv(&receivedMessage, ZMQ_NOBLOCK);
			g_Lua->Msg( "Got some data: %s\n", (const char *)receivedMessage.data() );
		//} else {
		//	g_Lua->Msg( "No Data\n" );
		//}

		//zmq::message_t sentMessage((void *)"thanks for the data", 19, 0);
		//socket.send(sentMessage, 0);
	} catch (zmq::error_t error) {
		int errno;
		errno = zmq_errno();
		if (errno) {
			g_Lua->Msg( "Error: %d %s\n", errno,  zmq_strerror(errno));
		}
	}
	return 0;
}

LUA_FUNCTION( ZmqSend )
{
	g_Lua->Msg( "Sending Data!\n" );
	// May be able to increase the number of threads here
	zmq::context_t context(3);
	zmq::socket_t socket(context, ZMQ_REQ);
	socket.connect("tcp://127.0.0.1:5555");
	zmq::message_t sentMessage((void *)"hello from gmod", 15, 0);
	socket.send(sentMessage, ZMQ_NOBLOCK);
	int errno;
	errno = zmq_errno();
	if (errno) {
		g_Lua->Msg( "Error: %d %s\n", errno,  zmq_strerror(errno));
	}
	return 0;
}

// Initialization
int Init( lua_State *L )
{
	g_Lua->SetGlobal( "PrintSomething", PrintSomething );
	g_Lua->SetGlobal( "ZmqVersion", ZmqVersion );
	g_Lua->SetGlobal( "ZmqReceive", ZmqReceive );
	g_Lua->SetGlobal( "ZmqSend", ZmqSend );
	g_Lua->SetGlobal( "ZmqInit", ZmqInit );
	g_Lua->Msg( "Simple Zmq Module Loaded!\n" );
	return 0;
}

// Shutdown
int Shutdown( lua_State *L )
{
	g_Lua->Msg("Module Unloaded!\n");
	return 0;
}