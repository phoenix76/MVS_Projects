#ifndef _WINFORM_H_
#define _WINFORM_H_

#include <Windows.h>
#include "CalcInfoHandler.h"

#define BUTTON_0 3000
#define BUTTON_1 3001
#define BUTTON_2 3002
#define BUTTON_3 3003
#define BUTTON_4 3004
#define BUTTON_5 3005
#define BUTTON_6 3006
#define BUTTON_7 3007
#define BUTTON_8 3008
#define BUTTON_9 3009
#define BUTTON_RESULT 3010			//=
#define BUTTON_DELETESYMBOL 3011	//Удалить один символ
#define BUTTON_REMOVEALL 3012		//Удалить все
#define BUTTON_SUM 3013				//+
#define BUTTON_DIFFERENCE 3014		//-
#define BUTTON_PRODUCT 3015			//*
#define BUTTON_QUOTIENT 3016		// "\"
#define BUTTON_MODULE 3017			//%
#define BUTTON_POINT 3018		// ,
#define BUTTON_EXIT 3019			// Выход
#define TEXTFIELD_ELEMENT 3020		//Поле ввода/вывода
#define BUTTON_ABOUT 3021			//Справка о программе

class cWinForm
{
public:

	void Run();
	bool Initialize();
	bool InitializeWindows();
	void Shutdown();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	HWND m_mainWnd;
	HWND m_buttonHandles[21];
	HWND m_textField;
	HINSTANCE m_hInstance;

	HBRUSH m_backgroundMainWnd;

	std::string test;
	cCalcInfoHandler *m_pInfoHandler;
};

static cWinForm *ApplicationHandle;
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif