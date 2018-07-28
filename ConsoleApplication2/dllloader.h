#pragma once

#ifndef _WIN32
#error ONLY FOR WINDOWS!
#endif

class MEM_LoadDllAPI
{
protected:
#ifdef _WIN64
	typedef unsigned long long DWORD;
#else
	typedef unsigned long DWORD;
#endif
public:
	virtual
		BOOL MemLoadLibrary(void *lpFileData, DWORD DataLength) = 0;
	virtual
		FARPROC MemGetProcAddress(LPCSTR lpProcName) = 0;
	virtual
		BOOL MemFreeLibrary() = 0;
};

MEM_LoadDllAPI*  GetMemLoadDllApp();

