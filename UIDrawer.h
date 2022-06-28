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

private:
    HDC _hdc;
    HWND _hwnd;
    RECT _rect;
    int _width;
    int _height;

    void drawText(TCHAR* text, int x, int y) const;
    void drawScore(int score, int x, int y) const;
    void drawSpeed(int speed, int x, int y) const;
    void drawNextFigure(Figure& figure, int x, int y);
};

