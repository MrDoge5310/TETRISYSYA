#include <windows.h>
#include<string>
#include <strstream> //for std::strstream
#include "Header.h"
#include "resource.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szCmdLine, int nCmdShow)
{
	WNDCLASS MainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		L"MainWndClass", MainClassProcedure);

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

LRESULT CALLBACK MainClassProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		case StartButtonClicked:

			int i = 0; //просто так что б не агрилось, потом реализую запуск цикла отсюда

		}
		break;

	case WM_PAINT:

		BeginPaint(hWnd, &ps);
		FillRect(ps.hdc, &GamingField, FieldBrush);
		EndPaint(hWnd, &ps);
		
		RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);

		BeginPaint(hWnd, &ps1);
		for (int i = 0; i < 4; i++)
		{
			square = Tfigure[i].FillRect(square); // тут по факту что и было раньше, только теперь через цикл рисуется каждый квадрат ффигурки

			
			FillRect(ps.hdc, &square, Blue);
			
		}
		EndPaint(hWnd, &ps1);

		break;

	case WM_CREATE:
		MainWndAddWidgets(hWnd);
		readThread = CreateThread(NULL, 0, MainCycle, NULL, 0, NULL); // создание потока
		break;

	case WM_KEYDOWN:	//обработка нажатий
		switch (LOWORD(wp))
		{
		case VK_LEFT: {
			for (int i = 0; i < 4; i++)
			{
				Tfigure[i].Move(-50, 0, -50, 0); // та же история что и в 62 строчке
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
		PostQuitMessage(0);
		CloseHandle(readThread); //закрітие потока но что-то вроде оно не работает
		ExitThread(0);
		break;


	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddWidgets(HWND hWnd)
{
	CreateWindowA("button", "Start", WS_VISIBLE | WS_CHILD | BS_CENTER, 550, 720, 150, 80, hWnd, (HMENU)StartButtonClicked, NULL, NULL);
	CreateWindowA("static", "Score:", WS_VISIBLE | WS_CHILD | ES_LEFT, 550, 670, 50, 20, hWnd, NULL, NULL, NULL);
	hScoreControl = CreateWindowA("static", "0", WS_VISIBLE | WS_CHILD | ES_LEFT, 600, 670, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Time:", WS_VISIBLE | WS_CHILD | ES_LEFT, 550, 600, 50, 20, hWnd, NULL, NULL, NULL);
	hTimer = CreateWindowA("static", "0", WS_VISIBLE | WS_CHILD | ES_LEFT, 600, 600, 100, 20, hWnd, NULL, NULL, NULL);
}

DWORD WINAPI MainCycle(LPVOID lParameter)		//главный цикл
{
	while (!GameOver) {
		for (int i = 0; i < 4; i++)
		{
			Tfigure[i].Move(0, 20, 0, 20);
			Tfigure[i].FillRect(square);
		}
		RedrawWindow(hMainWnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
		Sleep(250);
	}

	return 0;
}

