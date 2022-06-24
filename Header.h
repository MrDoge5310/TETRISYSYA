#pragma once

#define StartButtonClicked		1

HWND hScoreControl;
HWND hMainWnd;
HWND hChildWnd;

LRESULT CALLBACK ChildClassProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
LRESULT CALLBACK MainClassProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH bgcolor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);
WNDCLASS NewChildWindowClass(HBRUSH bgcolor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);

void MainWndAddWidgets(HWND hWnd);