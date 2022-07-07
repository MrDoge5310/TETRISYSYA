#pragma once

#define StartButtonClicked		1

PAINTSTRUCT ps;
HWND hMainWnd;
HWND hWndButton;

int timer = 0;

LRESULT CALLBACK MainClassProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASSEX NewWindowClass(HBRUSH bgcolor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);
HWND MainWndAddWidgets(HWND hWnd);
