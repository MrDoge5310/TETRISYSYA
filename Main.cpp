#include <windows.h>
#include <string>
#include "Header.h"
#include "UIDrawer.h"
#include "Tetris.h"
#include "resource.h"

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
		SCREEN_WIDTH * PIXEL_IN_BLOCK + 15,
		SCREEN_HEIGHT * PIXEL_IN_BLOCK + 145,
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
		hdc = GetDC(hWnd);
		hWndButton = MainWndAddWidgets(hWnd);

		// init game logic
		_speed = GAME_SPEED;

		ui = new UIDrawer(hdc, hWnd, PIXEL_IN_BLOCK, SCREEN_WIDTH, SCREEN_HEIGHT);
		tetris = new Tetris(*ui, SCREEN_WIDTH, SCREEN_HEIGHT, _speed);

		SetTimer(hWnd, TIMER_ID, _speed, NULL);

		ReleaseDC(hWnd, hdc);
		break;

	case WM_TIMER:
		_newSpeed = tetris->timerUpdate();

		if (_newSpeed != _speed) 
		{
			_speed = _newSpeed;
			KillTimer(hMainWnd, TIMER_ID);
			SetTimer(hWnd, TIMER_ID, _speed, NULL);
		}
		break;

	case WM_COMMAND:
		switch (wp)
		{
		case StartButtonClicked:
			if (tetris->isPaused())
			{
				SetWindowText(hWndButton, L"Pause");
				tetris->pause(false);
			}
			else
			{
				SetWindowText(hWndButton, L"Play");
				tetris->pause(true);
			}
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		tetris->repaint();
		EndPaint(hWnd, &ps);
		break;

	case WM_KEYDOWN:
		if (wp != VK_RETURN && tetris->isPaused())
			return DefWindowProc(hWnd, msg, wp, lp);

		switch (wp)
		{
		case VK_UP:
			tetris->rotateFigure();
			break;
		case VK_DOWN:
			tetris->moveFigure(0, -1);
			break;
		case VK_LEFT:
			tetris->moveFigure(-1, 0);
			break;
		case VK_RIGHT:
			tetris->moveFigure(1, 0);
			break;
		case VK_SPACE:
			tetris->rotateFigure();
			break;
		case VK_RETURN:
			tetris->restart();
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

HWND MainWndAddWidgets(HWND hWnd)
{
	int startButtonWIDTH = 70;
	int startButtonHEIGHT = 30;

	return CreateWindowA("button", "Pause",
		WS_VISIBLE | WS_CHILD | BS_CENTER, 
		(SCREEN_WIDTH * PIXEL_IN_BLOCK) / 2 - 40,
		SCREEN_HEIGHT * PIXEL_IN_BLOCK + 60,
		startButtonWIDTH,
		startButtonHEIGHT,
		hWnd, (HMENU)StartButtonClicked, NULL, NULL);
}
