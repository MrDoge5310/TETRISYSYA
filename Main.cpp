#include <windows.h>
#include <string>
#include "Header.h"
#include "UIDrawer.h"
#include "Tetris.h"
#include "resource.h"


const int PIXEL_IN_BLOCK = 30;  // One block size in pixels
const int SCREEN_WIDTH = 10;    // Game field width in blocks
const int SCREEN_HEIGHT = 20;   // Game field height in blocks
const int GAME_SPEED = 1000;      // Game update speed in milliseconds
const int TIMER_ID = 1;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szCmdLine, int nCmdShow)
{
	WNDCLASSEX MainClass = NewWindowClass(
		(HBRUSH)COLOR_WINDOW, 
		LoadCursor(NULL, IDC_ARROW), 
		hInst, 
		LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		L"MainWndClass", 
		MainClassProcedure);

	if (!RegisterClassEx(&MainClass)) { return -1; }

	MSG MainMessage = { 0 };

	hMainWnd = CreateWindow(L"MainWndClass", 
		L"Tetris",
		WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH * PIXEL_IN_BLOCK + 160,
		SCREEN_HEIGHT * PIXEL_IN_BLOCK + 30,
		NULL,
		NULL,
		hInst,
		NULL);

	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);

	while (GetMessage(&MainMessage, NULL, NULL, NULL))
	{
		TranslateMessage(&MainMessage);
		DispatchMessage(&MainMessage);
	}

	return 0;
}

WNDCLASSEX NewWindowClass(HBRUSH bgcolor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure) {

	WNDCLASSEX NWC = { 0 };

	NWC.cbSize = sizeof(WNDCLASSEX);
	NWC.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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
		tetris = new Tetris(*ui, SCREEN_WIDTH, SCREEN_HEIGHT, GAME_SPEED);


		SetTimer(hWnd, TIMER_ID, GAME_SPEED, NULL);

		ReleaseDC(hWnd, hdc);
		break;

	case WM_TIMER:
		tetris->timerUpdate();
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
		break;

	case WM_KEYDOWN:
		tetris->keyPress(wp);
		// move to Tetris class
		switch (LOWORD(wp))
		{
		case VK_LEFT: {
			for (int i = 0; i < 4; i++)
			{
				//Tfigure[i].Move(-50, 0, -50, 0);
			}
			break;
		}
		case VK_RIGHT: {
			for (int i = 0; i < 4; i++)
			{
				//Tfigure[i].Move(50, 0, 50, 0);
			}
			break;
		}
		case VK_DOWN: {
			for (int i = 0; i < 4; i++)
			{
				//Tfigure[i].Move(0, 50, 0, 50);
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
	int startButtonWIDTH = 70;
	int startButtonHEIGHT = 30;

	CreateWindowA("button", "Start",
		WS_VISIBLE | WS_CHILD | BS_CENTER, 
		SCREEN_WIDTH * PIXEL_IN_BLOCK - startButtonWIDTH + 110,
		SCREEN_HEIGHT * PIXEL_IN_BLOCK - startButtonHEIGHT - 30,
		startButtonWIDTH,
		startButtonHEIGHT,
		hWnd, (HMENU)StartButtonClicked, NULL, NULL);
}
