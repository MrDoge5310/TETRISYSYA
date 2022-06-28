#include <windows.h>
#include<string>
#include <strstream> //for std::strstream
#include "Header.h"
#include "UIDrawer.h"
#include "Tetris.h"
#include "resource.h"


const int PIXEL_IN_BLOCK = 20;  // One block size in pixels
const int SCREEN_WIDTH = 10;    // Game field width in blocks
const int SCREEN_HEIGHT = 20;   // Game field height in blocks
const int GAME_SPEED = 300;      // Game update speed in milliseconds
const int TIMER_ID = 1;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szCmdLine, int nCmdShow)
{
	WNDCLASS MainClass = NewWindowClass(
		(HBRUSH)COLOR_WINDOW, 
		LoadCursor(NULL, IDC_ARROW), 
		hInst, 
		LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		L"MainWndClass", 
		MainClassProcedure);

	if (!RegisterClassW(&MainClass)) { return -1; }

	MSG MainMessage = { 0 };

	hMainWnd = CreateWindow(L"MainWndClass", L"Tetris", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 300, 50, 850, 900, NULL, NULL, NULL, NULL);

	while (GetMessage(&MainMessage, NULL, NULL, NULL))
	{
		TranslateMessage(&MainMessage);
		DispatchMessage(&MainMessage);
	}

	return 0;
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

LRESULT CALLBACK MainClassProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) 
{
	HDC hdc;
	static UIDrawer* ui;
	static Tetris* tetris;

	switch (msg) 
	{
	case WM_CREATE:
		MainWndAddWidgets(hWnd);
		hdc = GetDC(hWnd);
		// init game logic
		ui = new UIDrawer(hdc, hWnd, PIXEL_IN_BLOCK, SCREEN_WIDTH, SCREEN_HEIGHT);
		tetris = new Tetris(*ui);

		SetTimer(hWnd, TIMER_ID, GAME_SPEED, NULL);

		ReleaseDC(hWnd, hdc);
		break;

	case WM_TIMER:
		tetris->timerUpdate();
		// temporary. Need to be moved into the Tetris class
		for (int i = 0; i < 4; i++)
		{
			Tfigure[i].Move(0, 20, 0, 20);
			Tfigure[i].FillRect(square);
		}
		RedrawWindow(hMainWnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
		break;

	case WM_COMMAND:
		switch (wp) {
		case StartButtonClicked:
			int i = 0;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		tetris->repaint();
		EndPaint(hWnd, &ps);

		// move to Tetris class
		BeginPaint(hWnd, &ps);
		FillRect(ps.hdc, &GamingField, FieldBrush);
		EndPaint(hWnd, &ps);
		
		RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);

		BeginPaint(hWnd, &ps1);
		for (int i = 0; i < 4; i++)
		{
			square = Tfigure[i].FillRect(square);
			FillRect(ps.hdc, &square, Blue);
			
		}
		EndPaint(hWnd, &ps1);

		break;

	case WM_KEYDOWN:
		tetris->keyPress(wp);
		// move to Tetris class
		switch (LOWORD(wp))
		{
		case VK_LEFT: {
			for (int i = 0; i < 4; i++)
			{
				Tfigure[i].Move(-50, 0, -50, 0);
			}
			break;
		}
		case VK_RIGHT: {
			for (int i = 0; i < 4; i++)
			{
				Tfigure[i].Move(50, 0, 50, 0);
			}
			break;
		}
		case VK_DOWN: {
			for (int i = 0; i < 4; i++)
			{
				Tfigure[i].Move(0, 50, 0, 50);
			}
			break;
		}

		default:
			break;
		}
		break;

	case WM_DESTROY:
		delete ui;
		delete tetris;
		PostQuitMessage(0);
		ExitThread(0);
		break;


	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddWidgets(HWND hWnd)
{
	CreateWindowA("button", "Start", WS_VISIBLE | WS_CHILD | BS_CENTER, 550, 720, 150, 80, hWnd, (HMENU)StartButtonClicked, NULL, NULL);
	CreateWindowA("static", "Score:", WS_VISIBLE | WS_CHILD | ES_LEFT, 550, 670, 50, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "0", WS_VISIBLE | WS_CHILD | ES_LEFT, 600, 670, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Time:", WS_VISIBLE | WS_CHILD | ES_LEFT, 550, 600, 50, 20, hWnd, NULL, NULL, NULL);
	hTimer = CreateWindowA("static", "0", WS_VISIBLE | WS_CHILD | ES_LEFT, 600, 600, 100, 20, hWnd, NULL, NULL, NULL);
}
