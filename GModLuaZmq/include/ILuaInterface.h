//=============================================================================//
//  ___  ___   _   _   _    __   _   ___ ___ __ __
// |_ _|| __| / \ | \_/ |  / _| / \ | o \ o \\ V /
//  | | | _| | o || \_/ | ( |_n| o ||   /   / \ / 
//  |_| |___||_n_||_| |_|  \__/|_n_||_|\\_|\\ |_|  2008
//										 
//=============================================================================//

#ifndef ILUAINTERFACE_H
#define ILUAINTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef _WIN32
#pragma once
#endif

#ifndef NO_SDK
#include "tier1/utlvector.h"
#endif

#ifdef UNICODE
#undef GetObject
#endif

// Forward Definitions
class ILuaObject;
class ILuaModuleManager;
struct lua_State;

// This struct is used to get a Lua table from Lua to C++
struct LuaKeyValue
{
	ILuaObject* pKey;
	ILuaObject* pValue;
};

#ifndef NO_SDK
typedef CUtlVector<LuaKeyValue> CUtlLuaVector;
#endif

typedef void (*VoidFunction) ( void );
typedef int (*CLuaFunction) (lua_State*);

// REDUNDANT. But removing will break backwards compatibility.
class LArgList;

namespace GLua
{
	enum
	{
		TYPE_INVALID = -1,
		TYPE_NIL, 
		TYPE_STRING, 
		TYPE_NUMBER, 
		TYPE_TABLE,
		TYPE_BOOL,
		TYPE_FUNCTION,
		TYPE_THREAD,

		// UserData
		TYPE_ENTITY, 
		TYPE_VECTOR, 
		TYPE_ANGLE,
		TYPE_PHYSOBJ,
		TYPE_SAVE,
		TYPE_RESTORE,
		TYPE_DAMAGEINFO,
		TYPE_EFFECTDATA,
		TYPE_MOVEDATA,
		TYPE_RECIPIENTFILTER,
		TYPE_USERCMD,
		TYPE_SCRIPTEDVEHICLE,

		// Client Only
		TYPE_MATERIAL,
		TYPE_PANEL,
		TYPE_PARTICLE,
		TYPE_PARTICLEEMITTER,
		TYPE_TEXTURE,
		TYPE_USERMSG,

		TYPE_CONVAR,
		TYPE_IMESH,
		TYPE_MATRIX,
		TYPE_SOUND,
		TYPE_PIXELVISHANDLE,
		TYPE_DLIGHT,
		TYPE_AISCHEDULE,

		TYPE_HTTPGET,

		TYPE_LIGHTUSERDATA,

		TYPE_COUNT
	};
}

//////////////////////////////////////////////////////////////////////////
//	Name: ILuaCallback
//////////////////////////////////////////////////////////////////////////
class ILuaCallback
{
	public:

		virtual ILuaObject* CreateLuaObject() = 0;
		virtual void DestroyLuaObject( ILuaObject* pObject) = 0;

		virtual void ErrorPrint( const char* strError ) = 0;
		virtual void Msg( const char* strMsg ) = 0;

		virtual bool CanRunScript( const char* strFilename, unsigned long CRC ) = 0;
		virtual void onRunScript( const char* strFilename, bool bRun, const char* strScriptContents ) = 0;
};


//////////////////////////////////////////////////////////////////////////
//	Name: ILuaInterface001
//////////////////////////////////////////////////////////////////////////
class ILuaInterface001
{
	public:

		virtual int			GetIRef( void ) = 0;
		virtual bool		Init( void ) = 0;

		virtual void		Shutdown( void ) = 0;
		virtual void		Cycle( void ) = 0;
		virtual void*		GetLuaState() = 0;

		// Stack
		virtual void		Pop( int i=1 ) = 0;

		// Get
		virtual void		GetGlobal( ILuaObject* obj, const char* name ) = 0;
		virtual ILuaObject*	GetGlobal( const char* name ) = 0;

		virtual ILuaObject*	GetObject( int i = -1 ) = 0;
		virtual const char* GetString( int i = -1 ) = 0;
		virtual int			GetInteger( int i = -1 ) = 0;
		virtual float		GetNumber( int i = -1 ) = 0;
		virtual bool		GetBool( int i = -1 ) = 0;

		virtual void**		GetUserDataPtr( int i = -1 ) = 0;
		virtual void*		GetUserData( int i = -1 ) = 0;


		virtual void		GetTable( int i = -1 ) = 0;

		// References
		virtual int			GetReference( int i = -1, bool bPopValue = false ) = 0;
		virtual void		FreeReference( int i ) = 0;
		virtual void		PushReference( int i )	= 0;

		// Push
		virtual void		Push( ILuaObject* ) = 0;
		virtual void		Push( const char* str ) = 0;
		virtual void		PushVA( const char* str, ... ) = 0;
		virtual void		Push( float f ) = 0;
		virtual void		Push( bool b ) = 0;
		virtual void		Push( CLuaFunction f ) = 0;

		virtual void		SetGlobal( const char* namename, ILuaObject* obj = 0 ) = 0;
		virtual void		SetGlobal( const char* namename, bool b ) = 0;
		virtual void		SetGlobal( const char* namename, float f ) = 0;
		virtual void		SetGlobal( const char* namename, const char* s ) = 0;
		virtual void		SetGlobal( const char* namename, CLuaFunction f ) = 0;
		virtual void		NewTable( void ) = 0;

		virtual void			LuaError( const char*, int argument = -1 ) = 0;
		virtual void			TypeError( const char* name, int argument ) = 0;
		virtual int				GetType( int iStackPos ) = 0;
		virtual const char*		GetTypeName( int iType ) = 0;

		virtual bool			Call( int args, int returns = 0 ) = 0;
		virtual bool			Call( ILuaObject* func, LArgList* in, LArgList* out = 0 ) = 0;
		virtual bool			Call( ILuaObject* func, LArgList* in, ILuaObject* member ) = 0;

		virtual void			SetMember( ILuaObject* table, const char* name ) = 0;
		virtual void			SetMember( ILuaObject* table, const char* namename, ILuaObject* member ) = 0;

		virtual int				Top( void ) = 0;

		virtual ILuaObject*		NewUserData( ILuaObject* obj ) = 0;
		virtual void			PushUserData( ILuaObject* metatable, void * v ) = 0;

		virtual void			NewGlobalTable( const char* ) = 0;
		virtual ILuaObject*		NewTemporaryObject( void ) = 0;

		virtual bool			isUserData( int i = -1 ) = 0;

		// GetMetaTable creates the meta table if it doesn't exist. Make sure type is unique to your
		// meta type. The default types are defined above (TYPE_INVALID etc). You should ideally make your type
		// some random large number that is in the 1000's - to be sure that it won't conflict with the base
		// meta types when more are added at a later date. Name isn't so important - it's just used for GetTypeName
		// and in Lua using type().
		virtual ILuaObject*		GetMetaTable( const char* strName, int Type ) = 0;
		virtual ILuaObject*		GetMetaTable( int i ) = 0; // Returns the metatable of an object on the stack
		virtual void			SetMetaTable( ILuaObject* obj, ILuaObject* metatable ) = 0;
		virtual void			CheckType( int i, int iType ) = 0;

		virtual ILuaObject*		GetReturn( int iNum ) = 0;

		// Added 10th December 2006
		virtual bool			IsServer( void ) = 0;
		virtual bool			IsClient( void ) = 0;
		virtual bool			IsDedicatedServer( void ) = 0;

		// Added 20th December 2006
		virtual void			SetMember( ILuaObject* table, float name ) = 0;
		virtual void			SetMember( ILuaObject* table, float namename, ILuaObject* member ) = 0;

		// Added 30th December 2006
		virtual ILuaObject*		GetNewTable( void ) = 0;		// Makes a new table and returns it

		// Added 09/Jan/2007
		virtual void			SetMember( ILuaObject* table, ILuaObject* key, ILuaObject* value ) = 0;

		// Added 12/01/2007
		virtual void			DebugPoint( void ) = 0;
};


//////////////////////////////////////////////////////////////////////////
//	Name: ILuaInterface
//////////////////////////////////////////////////////////////////////////
class ILuaInterface002 : public ILuaInterface001
{
	public:

		// See IModuleManager.h 
		virtual ILuaModuleManager* GetModuleManager( void ) = 0;

		// Set whether this is serverside, which prevents things like filename translating
		virtual void	SetIsServer( bool b ) = 0;

		// Pushes a LONG (CRCs etc)
		virtual void	PushLong( long f ) = 0;
		// Pushes value on stack to the top of the stack
		virtual void	PushValue( int i ) = 0;
		// Pushes a nil onto the stack
		virtual void PushNil( void ) = 0;
		// Returns a number. Item at stackpos can be a table, in which case all the 
		// numbers in the table will be |'d together to make the flag
		virtual int	GetFlags( int iStackPos ) = 0;

		// Quickly searches metatable of iObject for members iKey
		virtual bool	FindOnObjectsMetaTable( int iObject, int iKey ) = 0;
		// Quickly searches table using item on stack
		virtual bool	FindObjectOnTable( int iTable, int iKey ) = 0;
		// Quickly sets table member using items on the stack
		virtual void	SetMemberFast( ILuaObject* table, int iKey, int iValue ) = 0;

		// If bRun is false the string is converted to a function, which is left on top of the stack.
		virtual bool	RunString( const char* strFilename, const char* strPath, const char* strStringToRun, bool bRun, bool bShowErrors ) = 0;

		// Returns true if the objects are equal. May call metatables.
		virtual bool	IsEqual( ILuaObject* pObjectA, ILuaObject* pObjectB ) = 0;

		// Throws an error. Interrupts execution.
		virtual void	Error( const char* strError ) = 0;

		// Throws a type error if the string is NULL..
		virtual const char*		GetStringOrError( int i ) = 0;
		

		// C++ equivilent of 'require'
		virtual bool RunModule( const char* strName ) = 0;

		// Finds and runs a script.
		// If bRun is false, the script isn't run, but the 'function' block is left on the stack, ready to be run
		// Returns false if run was not successful
		virtual bool FindAndRunScript( const char* strFilename, bool bRun, bool bReportErrors ) = 0;

		// Internal use. Sets the search path ID to load Lua from.
		virtual void SetPathID( const char* ) = 0;
		virtual const char* GetPathID( void ) = 0;

		// Errors in the console without actually stopping the code from running
		virtual void ErrorNoHalt( const char* fmt, ... ) = 0;

		// Returns the Lua string length of string on stack. Lua strings can have NULLs.
		virtual int StringLength( int i ) = 0;

		// Simply sets the named global to nil
		virtual void RemoveGlobal( const char* strName ) = 0;

		// How many items are there on the stack
		virtual int GetStackTop( void ) = 0;

		// Gets the members from table on stack
		// Note: You MUST free the result when you're done using DeleteLuaVector.
#ifndef NO_SDK
		virtual CUtlLuaVector* GetAllTableMembers( int iTable ) = 0;
		virtual void DeleteLuaVector( CUtlLuaVector* pVector ) = 0;
#else
		virtual void* GetAllTableMembers( int iTable ) = 0;
		virtual void DeleteLuaVector( void* pVector ) = 0;
#endif
		// Simple Lua Msg. Is redirected to the ILuaCallback class, which
		// will display the text differently depending on which Lua instrance you're using.
		virtual void Msg( const char* fmt, ... ) = 0;

		// Used to push the path of the current folder onto a stack.
		// This allows us to load files relative to that folder.
		virtual void PushPath( const char* strPath ) = 0;
		virtual void PopPath( void ) = 0;
		virtual const char* GetPath( void ) = 0;

		// Used by the Lua file loading logic to determine whether it should
		// try to use downloaded files or just the regular ones.
		virtual bool ShouldTranslateLuaNames() = 0;
		virtual void SetShouldTranslateLuaNames( bool bTranslate ) = 0;

		// Push/Get a simple pointer. Not garbage collected, no metatables.
		virtual void PushLightUserData( void* pData ) = 0;
		virtual void* GetLightUserData( int i ) = 0;

};

//////////////////////////////////////////////////////////////////////////
//	Name: ILuaInterface
//////////////////////////////////////////////////////////////////////////
class ILuaInterface : public ILuaInterface002
{
	public:

		// Thread safety. 
		virtual void Lock() = 0;
		virtual void UnLock() = 0;

		virtual void SetGlobalDouble( const char* namename, double iValue ) = 0;

		virtual double GetDouble( int iPos ) = 0;
		virtual void PushDouble( double iInt ) = 0;
		
		// ScriptEnforcer "private" methods
};

extern ILuaInterface* g_Lua;

// Friendly Macros (Don't try to use these in modules, instead do Lua()->GetBool(1) etc)

#define Get_Bool( i ) (g_Lua->GetBool( i ))
#define Get_String( i ) (g_Lua->GetStringOrError( i ))
#define Get_Int( i ) (g_Lua->GetInteger( i ))
#define Get_Float( i ) (g_Lua->GetNumber( i ))
#define Get_LuaObject( i ) (g_Lua->GetObject( i ))

#define Is_Bool( i ) (g_Lua->GetType( i ) == GLua::TYPE_BOOL)
#define Is_Number( i ) (g_Lua->GetType( i ) == GLua::TYPE_NUMBER)
#define Is_String( i ) (g_Lua->GetType( i ) == GLua::TYPE_STRING)
#define Is_Table( i ) (g_Lua->GetType( i ) == GLua::TYPE_TABLE)
#define Is_Vector( i ) (g_Lua->GetType( i ) == GLua::TYPE_VECTOR)
#define Is_Type( i, type ) ( g_Lua->GetType( i ) == type )
#define Is_PhysObj( i ) ( g_Lua->GetType( i ) == GLua::TYPE_PHYSOBJ )

#define PrintLuaError g_Lua->ErrorNoHalt

#define Push_Float( i ) ( g_Lua->Push( (float) (i) ) )
#define Push_Int( i ) ( g_Lua->Push( (float) (i) ) )
#define Push_Bool( i ) ( g_Lua->Push( (bool) (i) ) )
#define Push_String( i ) ( g_Lua->Push( (const char*) (i) ) )
#define Push_Nil() ( g_Lua->Push( (ILuaObject*) (NULL) ) )
#define Push_Long( i ) ( g_Lua->PushLong( (long) (i) ) )

#define Return( i ) ( g_Lua->GetReturn(i) )

class CLuaLock
{
	public:

		CLuaLock() 
		{ 
			if (!g_Lua) return;
			g_Lua->Lock(); 
		}

		~CLuaLock() 
		{ 
			if (!g_Lua) return;
			g_Lua->UnLock(); 
		}
};

#endif // ILUAINTERFACE_H
