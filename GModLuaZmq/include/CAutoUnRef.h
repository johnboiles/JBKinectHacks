#include "ILuaObject.h"

#ifndef CAUTOUNREF_H
#define CAUTOUNREF_H

#ifdef _WIN32
#pragma once
#endif

class CAutoUnRef
{
public:
	CAutoUnRef() : m_pLuaObj(NULL)
	{
	};

	CAutoUnRef(ILuaObject *obj) : m_pLuaObj(obj)
	{
	};

	~CAutoUnRef()
	{
		if(!m_pLuaObj)
			return;

		m_pLuaObj->UnReference();
	};

	ILuaObject* operator -> () const
	{
		return m_pLuaObj;
	};

	operator ILuaObject*()
	{
		return m_pLuaObj;
	};

	operator ILuaObject*() const
	{
		return m_pLuaObj;
	};

	const CAutoUnRef& operator=(const ILuaObject *obj)
	{
		m_pLuaObj = (ILuaObject *)obj;
	}

private:
	ILuaObject *m_pLuaObj;
};

#endif // CAUTOUNREF_H