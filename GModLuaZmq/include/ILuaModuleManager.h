//=============================================================================//
//  ___  ___   _   _   _    __   _   ___ ___ __ __
// |_ _|| __| / \ | \_/ |  / _| / \ | o \ o \\ V /
//  | | | _| | o || \_/ | ( |_n| o ||   /   / \ / 
//  |_| |___||_n_||_| |_|  \__/|_n_||_|\\_|\\ |_|  2008
//										 
//=============================================================================//

#include "ILuaInterface.h"

class ILuaModuleManager
{
	public:

		virtual ILuaInterface*	GetLuaInterface( lua_State* pState ) = 0;
		virtual const char*		GetBaseFolder( void ) = 0;
};

extern ILuaModuleManager* modulemanager;

#define Lua() modulemanager->GetLuaInterface( L )