#pragma once

#define StartButtonClicked		1


HWND hScoreControl;
HWND hMainWnd;
HWND hChildWnd;
HWND hTimer;
HWND hWndButton;

HANDLE readThread;

bool GameOver = false;
bool colided = false;
int timer = 0;

RECT square;
RECT GamingField = { 400, 800, 60, 60 };
PAINTSTRUCT ps;

HBRUSH Blue = CreateSolidBrush(RGB(0, 0, 150));
HBRUSH FieldBrush = CreateSolidBrush(RGB(0, 0, 0));

LRESULT CALLBACK MainClassProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASSEX NewWindowClass(HBRUSH bgcolor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);


HWND MainWndAddWidgets(HWND hWnd);
