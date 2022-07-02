#pragma once

#define StartButtonClicked		1


HWND hScoreControl;
HWND hMainWnd;
HWND hChildWnd;
HWND hTimer;

HANDLE readThread;

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
	void Move(int X2, int Y2, int X1, int Y1)
	{
		x1 += X1;
		x2 += X2;
		y1 += Y1;
		y2 += Y2;

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
SquareClass s2(250, 110, 200, 160);
SquareClass s3(250, 160, 200, 210);
SquareClass s4(200, 110, 150, 160);
SquareClass Tfigure[4] = {s1, s2, s3, s4};

HBRUSH Blue = CreateSolidBrush(RGB(0, 0, 150));
HBRUSH FieldBrush = CreateSolidBrush(RGB(0, 0, 0));

LRESULT CALLBACK MainClassProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASSEX NewWindowClass(HBRUSH bgcolor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);


void MainWndAddWidgets(HWND hWnd);