// credit to LauCorp

#ifdef _WIN32
#pragma once
#endif

#define GMODLUASHAREDINTERFACE "LuaShared001"

struct ScriptData
{
	char path[MAX_PATH];
	int crc;
	char* contents;
	int timestamp;
	bool somebool;
};

#ifndef NO_SDK
	typedef CUtlVector<char[64]> AddonVector; // this may be a struct, but this can be solved with amazing C++ typedefs
#else
	typedef void* AddonVector;
#endif

class ILuaShared
{
public:
	virtual void			blah();
	virtual void			InitializeCommonInterfaces();
	virtual void			unknown01();
	virtual void			unknown02();
	virtual void			ParseContentTxt();
	virtual ScriptData*		LuaGetFile(const char *file);
	virtual void			LoadLua2();
	virtual void			PrintLuaStats();
	virtual void			unknown03();
	virtual void			unknown04();
	virtual void			MountGameContent();
	virtual void			LoadAddonInfo();
	virtual void			LoadGamemodes();
	virtual void			LoadAddonLua();
	virtual void			unknown05();
	virtual void			unknown06();
	virtual AddonVector*	GetLuaAddons();
	virtual void			unknown08();
	virtual void			unknown09();
	virtual void			unknown10();
	virtual void			unknown11();
	virtual void			unknown12();
	virtual void			unknown13();
	virtual void			unknown14();
	virtual void			unknown15();
};