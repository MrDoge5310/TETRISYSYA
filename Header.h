#pragma once

#define StartButtonClicked		1


HWND hScoreControl;
HWND hMainWnd;
HWND hChildWnd;
HWND hTimer;

bool GameOver = false;
bool colided = false;
int timer = 0;

class SquareClass
{
public:
	int x2;
	int y2;
	int x1;
	int y1;

	SquareClass(int X2, int Y2, int X1, int Y1)
	{
		x2 = X2;
		y2 = Y2;
		x1 = X1;
		y1 = Y1;
	}
	void Move()
	{
		y1 += 20;
		y2 += 20;

	}

	RECT FillRect(RECT r)
	{
		r = { x2, y2, x1, y1 };

		return r;
	}
};

RECT square;
RECT GamingField = { 400, 800, 60, 60 };
PAINTSTRUCT ps;
PAINTSTRUCT ps1;

SquareClass s1(250, 60, 200, 110);

HBRUSH Blue = CreateSolidBrush(RGB(0, 0, 150));
HBRUSH FieldBrush = CreateSolidBrush(RGB(0, 0, 0));

LRESULT CALLBACK MainClassProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH bgcolor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);


void MainWndAddWidgets(HWND hWnd);
void Timer();
void MainCycle();