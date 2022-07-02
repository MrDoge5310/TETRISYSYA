#pragma once
#include <windows.h>
#include "Figure.h"

class UIDrawer
{
public:
    UIDrawer(HDC hdc, HWND hwnd, int pxPerBlock, int width, int height);
    ~UIDrawer();

    void drawBlock(int x, int y, COLORREF color);
    void drawInterface();
    void drawGameOver();
    void drawPause();
    void DrawTimer();

private:
    HDC _hdc;
    HWND _hwnd;
    RECT _rect = {400, 800, 0, 0};
    int _width;
    int _height;
    wchar_t timetext[99999];
    int time = 0;
    //RECT timerRect = { 550, 600, 500, 500 };
    //PAINTSTRUCT timerps;

    void drawText(TCHAR* text, int x, int y) const;
    void drawScore(int score, int x, int y) const;
    void drawSpeed(int speed, int x, int y) const;
    void drawNextFigure(Figure& figure, int x, int y);
    
};

