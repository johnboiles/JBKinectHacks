//=============================================================================//
//  ___  ___   _   _   _    __   _   ___ ___ __ __
// |_ _|| __| / \ | \_/ |  / _| / \ | o \ o \\ V /
//  | | | _| | o || \_/ | ( |_n| o ||   /   / \ / 
//  |_| |___||_n_||_| |_|  \__/|_n_||_|\\_|\\ |_|  2008
//										 
//=============================================================================//

#ifndef ILUAOBJECT_H
#define ILUAOBJECT_H

#ifdef _WIN32
#pragma once
#endif

#include "ILuaInterface.h"

class ILuaObject;

//////////////////////////////////////////////////////////////////////////
//	Name: ILuaObject_001
//////////////////////////////////////////////////////////////////////////
class ILuaObject_001
{
	public:

		virtual void	Set( ILuaObject* obj ) = 0;
		virtual void	SetFromStack( int i ) = 0;
		virtual void	UnReference() = 0;

		virtual int				GetType( void ) = 0;

		virtual const char*		GetString( void ) = 0;
		virtual float			GetFloat( void ) = 0;
		virtual int				GetInt( void ) = 0;
		virtual void*			GetUserData( void ) = 0;

		virtual void			SetMember( const char* name ) = 0;
		virtual void			SetMember( const char* name, ILuaObject* obj ) = 0; // ( This is also used to set nil by passing NULL )
		virtual void			SetMember( const char* name, float val ) = 0;
		virtual void			SetMember( const char* name, bool val ) = 0;
		virtual void			SetMember( const char* name, const char* val ) = 0;
		virtual void			SetMember( const char* name, CLuaFunction f ) = 0;

		virtual bool			GetMemberBool( const char* name, bool b = true ) = 0;
		virtual int				GetMemberInt( const char* name, int i = 0 ) = 0;
		virtual float			GetMemberFloat( const char* name, float f = 0.0f ) = 0;
		virtual const char*		GetMemberStr( const char* name, const char* = "" ) = 0;
		virtual void*			GetMemberUserData( const char* name, void* = 0 ) = 0;
		virtual void*			GetMemberUserData( float name, void* = 0 ) = 0;
		virtual ILuaObject* 	GetMember( const char* name ) = 0;
		virtual ILuaObject* 	GetMember( ILuaObject* ) = 0;

		virtual void			SetMetaTable( ILuaObject* obj ) = 0;
		virtual void			SetUserData( void* obj ) = 0;

		virtual void			Push( void ) = 0;

		virtual bool			isNil() = 0;
		virtual bool			isTable() = 0;
		virtual bool			isString() = 0;
		virtual bool			isNumber() = 0;
		virtual bool			isFunction() = 0;
		virtual bool			isUserData() = 0;

		virtual ILuaObject* 	GetMember( float fKey ) = 0;

		virtual void*			Remove_Me_1( const char* name, void* = 0 ) = 0;

		virtual void			SetMember( float fKey ) = 0;
		virtual void			SetMember( float fKey, ILuaObject* obj ) = 0;
		virtual void			SetMember( float fKey, float val ) = 0;
		virtual void			SetMember( float fKey, bool val ) = 0;
		virtual void			SetMember( float fKey, const char* val ) = 0;
		virtual void			SetMember( float fKey, CLuaFunction f ) = 0;

		virtual const char*		GetMemberStr( float name, const char* = "" ) = 0;

		virtual void			SetMember( ILuaObject* k, ILuaObject* v ) = 0;
		virtual bool			GetBool( void ) = 0;

};


//////////////////////////////////////////////////////////////////////////
//	Name: ILuaObject
//////////////////////////////////////////////////////////////////////////
class ILuaObject : public ILuaObject_001
{
	public:

		// Push members to table from stack
		virtual bool			PushMemberFast( int iStackPos ) = 0;
		virtual void			SetMemberFast( int iKey, int iValue ) = 0;

		virtual void			SetFloat( float val ) = 0;
		virtual void			SetString( const char* val ) = 0;

		// Return members of table
#ifndef NO_SDK
		virtual CUtlLuaVector*	GetMembers( void ) = 0;
#else
		virtual void*	GetMembers( void ) = 0;
#endif

		// Set member 'pointer'. No GC, no metatables. 
		virtual void			SetMemberUserDataLite( const char* strKeyName, void* pData ) = 0;
		virtual void*			GetMemberUserDataLite( const char* strKeyName ) = 0;
};

#endif // ILUAOBJECT_H
