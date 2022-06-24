#include <windows.h>
#include "Header.h"
#include "resource.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szCmdLine, int nCmdShow)
{
	WNDCLASS MainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		L"MainWndClass", MainClassProcedure);

	WNDCLASS ChildClass = NewChildWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		L"MainWndClass", ChildClassProcedure);

	if (!RegisterClassW(&MainClass)) { return -1; }

	MSG MainMessage = { 0 };

	hMainWnd = CreateWindow(L"MainWndClass", L"Tetris", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 300, 50, 850, 900, NULL, NULL, NULL, NULL);
	hChildWnd = CreateWindow(L"MainWndClass", L"Gaming Field", WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD, 10, 10, 200, 200, hMainWnd, NULL , NULL, NULL);

	while (GetMessage(&MainMessage, NULL, NULL, NULL)) 
	{ 
		TranslateMessage(&MainMessage);
		DispatchMessage(&MainMessage);
	}

	return 0;
}

WNDCLASS NewChildWindowClass(HBRUSH bgcolor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure)
{
	WNDCLASS NCWC = { 0 };

	NCWC.hCursor = cursor;
	NCWC.hIcon = icon;
	NCWC.hInstance = hInst;
	NCWC.lpszClassName = name;
	NCWC.hbrBackground = bgcolor;
	NCWC.lpfnWndProc = procedure;

	return NCWC;
}


WNDCLASS NewWindowClass(HBRUSH bgcolor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure) {
	
	WNDCLASS NWC = { 0 };

	NWC.hCursor = cursor;
	NWC.hIcon = icon;
	NWC.hInstance = hInst;
	NWC.lpszClassName = name;
	NWC.hbrBackground = bgcolor;
	NWC.lpfnWndProc = procedure;

	return NWC;
}

LRESULT CALLBACK ChildClassProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CREATE:

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

LRESULT CALLBACK MainClassProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		case StartButtonClicked:
			SetWindowTextA(hScoreControl, "100");
			MessageBoxA(hWnd, "Game has started!", "Start", MB_OK);
			break;

		default: break;
		}
		break;

	case WM_CREATE:
		MainWndAddWidgets(hWnd);


		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddWidgets(HWND hWnd)
{
	 CreateWindowA ("button", "Start", WS_VISIBLE | WS_CHILD | BS_CENTER, 650, 750, 150, 80, hWnd, (HMENU)StartButtonClicked, NULL, NULL);
	 CreateWindowA("static", "Score:", WS_VISIBLE | WS_CHILD | ES_LEFT, 650, 700, 50, 50, hWnd, NULL, NULL, NULL);
	 hScoreControl = CreateWindowA("static", "0", WS_VISIBLE | WS_CHILD | ES_LEFT, 700, 700, 50, 50, hWnd, NULL, NULL, NULL);
}