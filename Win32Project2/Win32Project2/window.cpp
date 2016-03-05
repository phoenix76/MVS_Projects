#include "window.h"

HWND hWnd;

ATOM RegisterWndClass(
	HINSTANCE hInst,
	WNDPROC wndProc
	)
{
	WNDCLASSEXW wnd = { 0 };

	wnd.cbSize = sizeof(wnd);
	wnd.lpszClassName = L"HWND_MESSAGE_WND";
	wnd.lpfnWndProc = wndProc;
	wnd.hInstance = hInst;

	return RegisterClassExW(&wnd);
}

DWORD CreateMainWindow(
	HINSTANCE hInst,
	WNDPROC wndProc
	)
{
	ATOM regClass;

	if((regClass = RegisterWndClass(hInst, wndProc)) == 0)
	{
		return 1;
	}

	hWnd = CreateWindowW(
		(LPCWSTR)regClass,
		L"",
		0, 0, 0, 0, 0,
		HWND_MESSAGE,
		NULL,
		hInst,
		NULL
		);

	if(hWnd == NULL)
	{
		return 2;
	}

	return 0;
}

BOOL RunQueue(VOID)
{
	MSG  msg;
	BOOL bRet;

	while((bRet = GetMessageW(&msg, hWnd, 0, 0)) == TRUE)
	{
		if(bRet == -1)
		{
			bRet = FALSE;
			break;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return bRet;
}

HWND GetMainWindow(VOID)
{
	return hWnd;
}