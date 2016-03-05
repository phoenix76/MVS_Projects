#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <string>
#include <cctype>
#include <cstdlib>

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
#define BUTTON_DELETESUMBOL 3011	//Удалить один символ
#define BUTTON_REMOVEALL 3012		//Удалить все
#define BUTTON_SUM 3013				//+
#define BUTTON_DIFFERENCE 3014		//-
#define BUTTON_PRODUCT 3015			//*
#define BUTTON_QUOTIENT 3016		// "\"
#define BUTTON_MODULE 3017			//%
#define BUTTON_SEMICOLON 3018		// ,
#define BUTTON_EXIT 3019			// Выход
#define TEXTFIELD_ELEMENT 3020		//Поле ввода/вывода
#define BUTTON_ABOUT 3021			//Справка о программе

struct cValue
{
	std::string valueText;
	bool floatly;
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
char* CreateFullExpression(cValue, cValue, cValue, char);
HWND textField = NULL; //Текстовое поле ввода\вывода (статическое)

cValue value_1, value_2, result;
std::string fullExpression;
char operationType = '0';
unsigned short editValue = 1;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND buttonHandles[21];
	HWND m_hWnd = NULL;
	
	WNDCLASSEX wc;
	HBRUSH backgroundMainWnd = CreateSolidBrush(RGB(219, 215, 210));

	value_1.floatly = value_2.floatly = result.floatly = false;//По умолчанию все опернды целочисленные

	ZeroMemory(&wc, sizeof(wc));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = "CalculateWnd";
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hbrBackground = backgroundMainWnd;

	if(!RegisterClassEx(&wc))
	{
		MessageBox(m_hWnd, "Error register class", "Error", MB_OK);
		return false;
	}

	m_hWnd = CreateWindowEx(NULL, "CalculateWnd", "Калькулятор", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 870, 400, 190, 360, NULL, NULL, hInstance, NULL);
	if(!m_hWnd)
	{
		MessageBox(m_hWnd, "Error create window", "Error", MB_OK);
		return false;
	}

	for(int i = 0; i < 21; i++)
		buttonHandles[i] = NULL;

	buttonHandles[0] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "EX", WS_CHILD | WS_VISIBLE, 10, 120, 30, 30, m_hWnd, (HMENU)BUTTON_EXIT, hInstance, NULL);
	buttonHandles[1] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "CA", WS_VISIBLE | WS_CHILD, 50, 120, 30, 30, m_hWnd, (HMENU)BUTTON_REMOVEALL, hInstance, NULL);
	buttonHandles[2] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "C", WS_VISIBLE | WS_CHILD, 90, 120, 30, 30, m_hWnd, (HMENU)BUTTON_DELETESUMBOL, hInstance, NULL);
	buttonHandles[3] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "+", WS_VISIBLE | WS_CHILD, 130, 120, 30, 30, m_hWnd, (HMENU)BUTTON_SUM, hInstance, NULL);
	buttonHandles[4] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "0", WS_VISIBLE | WS_CHILD, 10, 160, 30, 30, m_hWnd, (HMENU)BUTTON_0, hInstance, NULL);
	buttonHandles[5] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "1", WS_VISIBLE | WS_CHILD, 50, 160, 30, 30, m_hWnd, (HMENU)BUTTON_1, hInstance, NULL);
	buttonHandles[6] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "2", WS_VISIBLE | WS_CHILD, 90, 160, 30, 30, m_hWnd, (HMENU)BUTTON_2, hInstance, NULL);
	buttonHandles[7] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "-", WS_VISIBLE | WS_CHILD, 130, 160, 30, 30, m_hWnd, (HMENU)BUTTON_DIFFERENCE, hInstance, NULL);
	buttonHandles[8] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "3", WS_VISIBLE | WS_CHILD, 10, 200, 30, 30, m_hWnd, (HMENU)BUTTON_3, hInstance, NULL);
	buttonHandles[9] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "4", WS_VISIBLE | WS_CHILD, 50, 200, 30, 30, m_hWnd, (HMENU)BUTTON_4, hInstance, NULL);
	buttonHandles[10] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "5", WS_VISIBLE | WS_CHILD, 90, 200, 30, 30, m_hWnd, (HMENU)BUTTON_5, hInstance, NULL);
	buttonHandles[11] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "*", WS_VISIBLE | WS_CHILD, 130, 200, 30, 30, m_hWnd, (HMENU)BUTTON_PRODUCT, hInstance, NULL);
	buttonHandles[12] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "6", WS_VISIBLE | WS_CHILD, 10, 240, 30, 30, m_hWnd, (HMENU)BUTTON_6, hInstance, NULL);
	buttonHandles[13] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "7", WS_VISIBLE | WS_CHILD, 50, 240, 30, 30, m_hWnd, (HMENU)BUTTON_7, hInstance, NULL);
	buttonHandles[14] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "8", WS_VISIBLE | WS_CHILD, 90, 240, 30, 30, m_hWnd, (HMENU)BUTTON_8, hInstance, NULL);
	buttonHandles[15] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "/", WS_VISIBLE | WS_CHILD, 130, 240, 30, 30, m_hWnd, (HMENU)BUTTON_QUOTIENT, hInstance, NULL);
	buttonHandles[16] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "9", WS_VISIBLE | WS_CHILD, 10, 280, 30, 30, m_hWnd, (HMENU)BUTTON_9, hInstance, NULL);
	buttonHandles[17] = CreateWindowEx(WS_EX_STATICEDGE, "Button", ",", WS_VISIBLE | WS_CHILD, 50, 280, 30, 30, m_hWnd, (HMENU)BUTTON_SEMICOLON, hInstance, NULL);
	buttonHandles[18] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "=", WS_VISIBLE | WS_CHILD, 90, 280, 30, 30, m_hWnd, (HMENU)BUTTON_RESULT, hInstance, NULL);
	buttonHandles[19] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "%", WS_VISIBLE | WS_CHILD, 130, 280, 30, 30, m_hWnd, (HMENU)BUTTON_MODULE, hInstance, NULL);
	buttonHandles[20] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "О программе...", WS_VISIBLE | WS_CHILD, 10, 80, 150, 30, m_hWnd, (HMENU)BUTTON_ABOUT, hInstance, NULL);
	textField = CreateWindowEx(WS_EX_CLIENTEDGE, "Static", "", WS_VISIBLE | WS_CHILD, 10, 10, 150, 60, m_hWnd, (HMENU)TEXTFIELD_ELEMENT, hInstance, NULL);

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnregisterClass("CalculateWnd", hInstance);
	DestroyWindow(m_hWnd);

	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	//case WM_PAINT:
		//return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch(wParam)
		{
		case BUTTON_EXIT:
			PostQuitMessage(0);
			return 0;

		case BUTTON_ABOUT:
			MessageBox(hwnd, "Calculator v1.0\nCreated by DSOFT 22.10.2015\nAll rights reserved", "About", MB_OK);
			return 0;

		case BUTTON_0:
			SetWindowText(textField, "Тут текст");
			return 0;

		case BUTTON_1:
			return 0;

		case BUTTON_REMOVEALL:
			SetWindowText(textField, "");
			return 0;
		}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
char* CreateFullExpression(cValue val_1 , cValue val_2, cValue result, char operationType)
{
	char* returningExpression = NULL;
	if(!std::isdigit(val_2.valueText[0]) && operationType == '0')
	{
		std::strcpy(returningExpression, val_1.valueText.c_str());
		return returningExpression;
	}

	//return returningExpression;
}