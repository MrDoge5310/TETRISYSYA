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

    void drawScore(int score, int x, int y);
    void drawSpeed(int speed, int x, int y);
    void drawNextFigure(Figure& figure, int x, int y);

private:
    HDC _hdc;
    HWND _hwnd;
    RECT _rect;
    int _width;
    int _height;
};

