#pragma once

#define StartButtonClicked		1


HWND hScoreControl;
HWND hMainWnd;
HWND hChildWnd;
HWND hTimer;

bool GameStarted = false;
bool colided = false;
//int timer = 0;

class SquareClass
{
public:
	int x2;
	int y2;
	int x1;
	int y1;

	SquareClass(int X, int Y)
	{
		x2 = X+40;
		y2 = Y+40;
		x1 = X;
		y1 = Y;
	}
	void Move(int X, int Y)
	{
		if ((x2 + X) <= 400) {
			x1 += X;
			x2 += X;
		}
		else {
			x1 -= X;
			x2 -= X;
		}
		y1 += Y;
		y2 += Y;

		if (y2 >= 800)
		{
			colided = true;
		}

	}

	RECT FillRect(RECT r)
	{
		r = { x2, y2, x1, y1 };

		return r;
	}
};

RECT square;
//RECT GamingField = { 500, 1000, 50, 50 };
PAINTSTRUCT ps;
PAINTSTRUCT ps1;

SquareClass s1(200, 0);
SquareClass s2(200, 40);
SquareClass s3(200, 80);
SquareClass s4(160, 40);
SquareClass Tfigure[4] = {s1, s2, s3, s4};

HBRUSH Blue = CreateSolidBrush(RGB(0, 0, 150));
//HBRUSH FieldBrush = CreateSolidBrush(RGB(0, 0, 0));

LRESULT CALLBACK MainClassProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH bgcolor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);


void MainWndAddWidgets(HWND hWnd);