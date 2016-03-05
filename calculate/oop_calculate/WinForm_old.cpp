#include "WinForm.h"

void cWinForm::Run()
{
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnregisterClass("Calculator", m_hInstance);
	DestroyWindow(m_mainWnd);
}
bool cWinForm::Initialize()
{
	m_mainWnd = NULL;
	test = "test";
	for(short count = 0; count < 21; count++)
		m_buttonHandles[count] = NULL;
	m_textField = NULL;
	m_hInstance = NULL;
	m_backgroundMainWnd = CreateSolidBrush(RGB(219, 215, 210));
	m_pInfoHandler = new cCalcInfoHandler;

	if(!InitializeWindows())
	{
		MessageBox(m_mainWnd, "Error Initialize()", "Error", MB_OK);
		return false;
	}

	return true;
}
bool cWinForm::InitializeWindows()
{
	ApplicationHandle = this;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(wc));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(wc);
	wc.lpszClassName = "Calculator";
	wc.lpszMenuName = NULL;
	wc.hbrBackground = m_backgroundMainWnd;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hInstance = m_hInstance;
	wc.lpfnWndProc = WndProc;

	if(!RegisterClassEx(&wc))
	{
		MessageBox(m_mainWnd, "Error register class", "Error", MB_OK);
		return false;
	}

	m_mainWnd = CreateWindowEx(NULL, "Calculator", "Калькулятор", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 870, 400, 190, 360, NULL, NULL, m_hInstance, NULL);
	if(!m_mainWnd)
	{
		MessageBox(m_mainWnd, "Error create main window", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[0] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "EX", WS_VISIBLE | WS_CHILD, 10, 120, 30, 30, m_mainWnd, (HMENU)BUTTON_EXIT, m_hInstance, NULL);
	if(!m_buttonHandles[0])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_EXIT", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[1] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "CA", WS_VISIBLE | WS_CHILD, 50, 120, 30, 30, m_mainWnd, (HMENU)BUTTON_REMOVEALL, m_hInstance, NULL);
	if(!m_buttonHandles[1])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_REMOVEALL", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[2] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "C", WS_VISIBLE | WS_CHILD, 90, 120, 30, 30, m_mainWnd, (HMENU)BUTTON_DELETESYMBOL, m_hInstance, NULL);
	if(!m_buttonHandles[2])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_DELETESYMBOL", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[3] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "+", WS_VISIBLE | WS_CHILD, 130, 120, 30, 30, m_mainWnd, (HMENU)BUTTON_SUM, m_hInstance, NULL);
	if(!m_buttonHandles[3])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_SUM", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[4] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "0", WS_VISIBLE | WS_CHILD, 10, 160, 30, 30, m_mainWnd, (HMENU)BUTTON_0, m_hInstance, NULL);
	if(!m_buttonHandles[4])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_0", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[5] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "1", WS_VISIBLE | WS_CHILD, 50, 160, 30, 30, m_mainWnd, (HMENU)BUTTON_1, m_hInstance, NULL);
	if(!m_buttonHandles[5])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_1", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[6] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "2", WS_VISIBLE | WS_CHILD, 90, 160, 30, 30, m_mainWnd, (HMENU)BUTTON_2, m_hInstance, NULL);
	if(!m_buttonHandles[6])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_2", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[7] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "-", WS_VISIBLE | WS_CHILD, 130, 160, 30, 30, m_mainWnd, (HMENU)BUTTON_DIFFERENCE, m_hInstance, NULL);
	if(!m_buttonHandles[7])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_DIFFERENCE", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[8] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "3", WS_VISIBLE | WS_CHILD, 10, 200, 30, 30, m_mainWnd, (HMENU)BUTTON_3, m_hInstance, NULL);
	if(!m_buttonHandles[8])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_3", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[9] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "4", WS_VISIBLE | WS_CHILD, 50, 200, 30, 30, m_mainWnd, (HMENU)BUTTON_4, m_hInstance, NULL);
	if(!m_buttonHandles[9])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_4", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[10] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "5", WS_VISIBLE | WS_CHILD, 90, 200, 30, 30, m_mainWnd, (HMENU)BUTTON_5, m_hInstance, NULL);
	if(!m_buttonHandles[10])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_5", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[11] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "*", WS_VISIBLE | WS_CHILD, 130, 200, 30, 30, m_mainWnd, (HMENU)BUTTON_PRODUCT, m_hInstance, NULL);
	if(!m_buttonHandles[11])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_PRODUCT", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[12] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "6", WS_VISIBLE | WS_CHILD, 10, 240, 30, 30, m_mainWnd, (HMENU)BUTTON_6, m_hInstance, NULL);
	if(!m_buttonHandles[12])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_6", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[13] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "7", WS_VISIBLE | WS_CHILD, 50, 240, 30, 30, m_mainWnd, (HMENU)BUTTON_7, m_hInstance, NULL);
	if(!m_buttonHandles[13])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_7", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[14] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "8", WS_VISIBLE | WS_CHILD, 90, 240, 30, 30, m_mainWnd, (HMENU)BUTTON_8, m_hInstance, NULL);
	if(!m_buttonHandles[14])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_8", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[15] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "/", WS_VISIBLE | WS_CHILD, 130, 240, 30, 30, m_mainWnd, (HMENU)BUTTON_QUOTIENT, m_hInstance, NULL);
	if(!m_buttonHandles[15])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_QUOTIENT", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[16] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "9", WS_VISIBLE | WS_CHILD, 10, 280, 30, 30, m_mainWnd, (HMENU)BUTTON_9, m_hInstance, NULL);
	if(!m_buttonHandles[16])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_9", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[17] = CreateWindowEx(WS_EX_STATICEDGE, "Button", ".", WS_VISIBLE | WS_CHILD, 50, 280, 30, 30, m_mainWnd, (HMENU)BUTTON_POINT, m_hInstance, NULL);
	if(!m_buttonHandles[17])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_POINT", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[18] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "=", WS_VISIBLE | WS_CHILD, 90, 280, 30, 30, m_mainWnd, (HMENU)BUTTON_RESULT, m_hInstance, NULL);
	if(!m_buttonHandles[18])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_RESULT", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[19] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "%", WS_VISIBLE | WS_CHILD, 130, 280, 30, 30, m_mainWnd, (HMENU)BUTTON_MODULE, m_hInstance, NULL);
	if(!m_buttonHandles[19])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_MODULE", "Error", MB_OK);
		return false;
	}
	m_buttonHandles[20] = CreateWindowEx(WS_EX_STATICEDGE, "Button", "О программе...", WS_VISIBLE | WS_CHILD, 10, 80, 150, 30, m_mainWnd, (HMENU)BUTTON_ABOUT, m_hInstance, NULL);
	if(!m_buttonHandles[20])
	{
		MessageBox(m_mainWnd, "Error create BUTTON_ABOUT", "Error", MB_OK);
		return false;
	}
	m_textField = CreateWindowEx(WS_EX_CLIENTEDGE, "Static", "", WS_VISIBLE | WS_CHILD, 10, 10, 150, 60, m_mainWnd, (HMENU)TEXTFIELD_ELEMENT, m_hInstance, NULL);
	if(!m_textField)
	{
		MessageBox(m_mainWnd, "Error create TEXTFIELD_ELEMENT", "Error", MB_OK);
		return false;
	}

	ShowWindow(m_mainWnd, SW_SHOW);
	UpdateWindow(m_mainWnd);

	return true;
}
LRESULT CALLBACK cWinForm::MessageHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_COMMAND:
		switch(wParam)
		{
		case BUTTON_0:
			
			break;

		case BUTTON_1:
			
			break;

		case BUTTON_2:
			
			return 0;

		case BUTTON_3:
			
			return 0;

		case BUTTON_4:
			
			return 0;

		case BUTTON_5:
			
			return 0;

		case BUTTON_6:
			
			return 0;

		case BUTTON_7:
			
			return 0;

		case BUTTON_8:
			
			return 0;

		case BUTTON_9:
			
			return 0;

		case BUTTON_RESULT:
			
			break;

		case BUTTON_DELETESYMBOL:
			
			break;

		case BUTTON_REMOVEALL:
			
			break;

		case BUTTON_SUM:
			
			break;

		case BUTTON_DIFFERENCE:
			
			break;

		case BUTTON_PRODUCT:
			
			break;

		case BUTTON_QUOTIENT:
			
			break;

		case BUTTON_MODULE:
			
			break;

		case BUTTON_POINT:
		
			break;
		
		case BUTTON_EXIT:
			PostQuitMessage(0);
			return 0;

		case BUTTON_ABOUT:
			MessageBox(hwnd, "Calculator v1.01\nCreated by DSOFT 22.10.2015\nAll rights reserved", "About", MB_OK);
			break;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		return 0;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
void cWinForm::Shutdown()
{
	delete m_pInfoHandler;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wParam, LPARAM lParam)
{
	switch(umessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	default:
		return ApplicationHandle->MessageHandler(hwnd, umessage, wParam, lParam);
	}
}