#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <Windows.h>

DWORD CreateMainWindow(
	HINSTANCE hInst,
	WNDPROC wnd
	);

BOOL RunQueue(VOID);

HWND GetMainWindow(VOID);

#endif // _WINDOW_H_
