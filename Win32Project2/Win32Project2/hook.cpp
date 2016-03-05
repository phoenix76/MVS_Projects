#include "hook.h"

BOOL InstallHook(
	PHOOK_INFO hook,
	int hookId
	)
{
	if(hook == NULL)
		return FALSE;

	hook->hHook = SetWindowsHookExW(hookId, hook->lpfnHookProc, hook->hInst, 0);
	return hook->hHook != NULL;
}

BOOL UninstallHook(
	PHOOK_INFO hook
	)

{
	BOOL bRet;

	if(hook == NULL)
		return FALSE;

	if((bRet = UnhookWindowsHookEx(hook->hHook)) == TRUE)
		hook->hHook = NULL;
}