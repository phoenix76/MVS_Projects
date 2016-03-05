#ifndef _DEBUG_H_
#define _DEBUG_H_

extern "C"

#ifdef _DEBUG
#pragma comment(lib, "C:\\WinDDK\\7600.16385.1\\lib\\win7\\i386\\ntdll.lib")

__declspec(dllimport) __cdecl DbgPrint(
	__in PCHAR Format,
	...
	);
#endif // _DEBUG

#endif // _DEBUG_H_