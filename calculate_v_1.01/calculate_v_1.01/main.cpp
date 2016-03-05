#include "WinForm.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	cWinForm *System = new cWinForm;

	if(System->Initialize())
		System->Run();
	else
		return 1;

	delete System;

	return 0;
}