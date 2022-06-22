#include <windows.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreviousInst, LPSTR lpCommandLine, int nCommandShow)
{
    // создаём дескриптор окна
    // описываем класс окна
    // создаём окошко, показываем его на экране
    // возвращаем значение при неудаче или при выходе

    HWND hMainWnd;

    WNDCLASSEX wc;
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WNDPROC;


}