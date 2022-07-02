#include "UIDrawer.h"

UIDrawer::UIDrawer(HDC hdc, HWND hwnd, int blockPixels, int width, int height)
{
    _hdc = hdc;
    _hwnd = hwnd;
    _width = width;
    _height = height;

    //GetClientRect(hwnd, &_rect);

    SaveDC(hdc);

    SetTextColor(hdc, RGB(255, 255, 255));
}

UIDrawer::~UIDrawer()
{
    RestoreDC(_hdc, -1);
}

void UIDrawer::drawBlock(int x, int y, COLORREF color)
{
    
}

void UIDrawer::drawInterface()
{
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
    //_rect.top = _height * 40;
    //_rect.left = _width * 40;
    //_rect.bottom = 60;
    //_rect.right = _width + 8;
    FillRect(_hdc, &_rect, hBrush);
    DeleteObject(hBrush);
}

void UIDrawer::DrawTimer()
{
    //time++;
    //wsprintf(timetext, TEXT("Time: %d"), time);
    //DrawText(_hdc, timetext, 99999, &timerRect, DT_LEFT | DT_NOCLIP);

    //SetWindowText(hTimer, timetext);s
}

void UIDrawer::drawGameOver()
{
}

void UIDrawer::drawPause()
{
}

void UIDrawer::drawText(TCHAR* szText, int x, int y) const
{
}

void UIDrawer::drawScore(int score, int x, int y) const
{
}

void UIDrawer::drawSpeed(int speed, int x, int y) const
{
}

void UIDrawer::drawNextFigure(Figure& figure, int x, int y)
{
}