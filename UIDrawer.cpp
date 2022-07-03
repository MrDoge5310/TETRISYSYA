#include "UIDrawer.h"

UIDrawer::UIDrawer(HDC hdc, HWND hwnd, int blockPixels, int width, int height)
{
    _hdc = hdc;
    _hwnd = hwnd;
    _width = width;
    _height = height;

    GetClientRect(hwnd, &_rect);

    SaveDC(hdc);

    // Default colors for ui
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 255));
    SetBkColor(hdc, RGB(80, 80, 80));

    // Coordinate system
    SetMapMode(hdc, MM_ISOTROPIC);
    SetViewportExtEx(hdc, blockPixels, blockPixels, 0);
    SetWindowExtEx(hdc, 1, -1, 0);
    SetViewportOrgEx(hdc, 0, _rect.bottom, 0);
}

UIDrawer::~UIDrawer()
{
    RestoreDC(_hdc, -1);
}

void UIDrawer::drawBlock(int x, int y, COLORREF color)
{
    HBRUSH hBrush = CreateSolidBrush(color);
    _rect.left = x;
    _rect.right = x + 1;
    _rect.top = y;
    _rect.bottom = y + 1;

    FillRect(_hdc, &_rect, hBrush);

    // Draw black border
    MoveToEx(_hdc, x, y + 1, NULL);
    LineTo(_hdc, x, y);
    LineTo(_hdc, x + 1, y);
    DeleteObject(hBrush);
}

void UIDrawer::drawInterface()
{
    HBRUSH hBrush = CreateSolidBrush(RGB(80, 80, 80));
    _rect.top = _height;
    _rect.left = _width;
    _rect.bottom = 0;
    _rect.right = _width + 8;
    FillRect(_hdc, &_rect, hBrush);
    DeleteObject(hBrush);
}

void UIDrawer::drawGameOver()
{
    //drawText(TEXT("GAME OVER"), 3, 10);
    //drawText(TEXT("Press ENTER to restart"), 2, 9);
    TCHAR szBuffer[20];
    int len = wsprintf(szBuffer, TEXT("GAME OVER"));
    SetBkMode(_hdc, OPAQUE);
    TextOut(_hdc, 3, 10, szBuffer, len);
    SetBkMode(_hdc, TRANSPARENT);
}

void UIDrawer::drawPause()
{
    //drawText(TEXT("PAUSE"), 4, 10);
    //drawText(TEXT("Press PAUSE again to continue"), 1, 9)

    TCHAR szBuffer[20];
    int len = wsprintf(szBuffer, TEXT("PAUSE"));
    SetBkMode(_hdc, OPAQUE);
    TextOut(_hdc, 4, 10, szBuffer, len);
    SetBkMode(_hdc, TRANSPARENT);
}

void UIDrawer::drawScore(int score, int x, int y)
{
    TCHAR szBuffer[20];
    int len = wsprintf(szBuffer, TEXT("Score: %6d"), score);
    SetBkMode(_hdc, OPAQUE);
    TextOut(_hdc, x, y, szBuffer, len);
    SetBkMode(_hdc, TRANSPARENT);
}

void UIDrawer::drawSpeed(int speed, int x, int y)
{
    TCHAR szBuffer[20];
    int len = wsprintf(szBuffer, TEXT("Speed: %6d"), speed);
    SetBkMode(_hdc, OPAQUE);
    TextOut(_hdc, x, y, szBuffer, len);
    SetBkMode(_hdc, TRANSPARENT);
}

void UIDrawer::drawNextFigure(Figure& figure, int x, int y)
{
}