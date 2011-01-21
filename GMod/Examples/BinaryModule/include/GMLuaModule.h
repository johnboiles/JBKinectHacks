//=============================================================================//
//  ___  ___   _   _   _    __   _   ___ ___ __ __
// |_ _|| __| / \ | \_/ |  / _| / \ | o \ o \\ V /
//  | | | _| | o || \_/ | ( |_n| o ||   /   / \ / 
//  |_| |___||_n_||_| |_|  \__/|_n_||_|\\_|\\ |_|  2008
//										 
//=============================================================================//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "ILuaInterface.h"
#include "ILuaObject.h"

#include "ILuaModuleManager.h"

#include "CAutoUnRef.h"

#if defined _WIN32 || defined __CYGWIN__
	#ifdef __GNUC__
		#define GM_DLL_EXPORT __attribute__((dllexport))
	#else
		#define GM_DLL_EXPORT __declspec(dllexport)
	#endif
#else
	#if __GNUC__ >= 4
		#define GM_DLL_EXPORT __attribute__ ((visibility("default")))
	#else
		#define GM_DLL_EXPORT
	#endif
#endif

// You should place this at the top of your module
#define GMOD_MODULE( _startfunction_, _closefunction_ ) 			\
	ILuaModuleManager* modulemanager = NULL;						\
	int _startfunction_( lua_State* L );							\
	int _closefunction_( lua_State* L );							\
	extern "C" int GM_DLL_EXPORT gmod_open( ILuaInterface* i ) 		\
	{																\
		modulemanager = i->GetModuleManager();						\
		return _startfunction_( (lua_State*)(i->GetLuaState()) );	\
	}																\
	extern "C" int GM_DLL_EXPORT gmod_close( lua_State* L )			\
	{																\
		_closefunction_( L );										\
		return 0;													\
	}

#define LUA_FUNCTION( _function_ ) static int _function_( lua_State* L )