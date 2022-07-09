#pragma once

#define StartButtonClicked		1

const int PIXEL_IN_BLOCK = 30;  // One block size in pixels
const int SCREEN_WIDTH = 10;    // Game field width in blocks
const int SCREEN_HEIGHT = 20;   // Game field height in blocks
int GAME_SPEED = 300;      // Game update speed in milliseconds
const int TIMER_ID = 1;

PAINTSTRUCT ps;
HWND hMainWnd;
HWND hWndButton;

LRESULT CALLBACK MainClassProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASSEX NewWindowClass(HBRUSH bgcolor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);
HWND MainWndAddWidgets(HWND hWnd);

int newspeed;
UINT ChangeSpeed(int newspeed);
