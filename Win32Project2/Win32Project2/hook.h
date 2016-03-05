#ifndef _HOOK_H_
#define _HOOK_H_

#include <Windows.h>

typedef struct _HOOK_INFO {
	HOOKPROC  lpfnHookProc;
	HHOOK     hHook;
	HINSTANCE hInst;
} HOOK_INFO, *PHOOK_INFO;

BOOL InstallHook(
	PHOOK_INFO hook,
	int idHook
	);

BOOL UninstallHook(
	PHOOK_INFO hook
	);

#endif // _HOOK_H_
