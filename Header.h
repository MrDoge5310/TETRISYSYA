#pragma once

#define StartButtonClicked		1


HWND hScoreControl;
HWND hMainWnd;
HWND hChildWnd;
HWND hTimer;

PAINTSTRUCT ps;


LRESULT CALLBACK MainClassProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASSEX NewWindowClass(HBRUSH bgcolor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);


void MainWndAddWidgets(HWND hWnd);