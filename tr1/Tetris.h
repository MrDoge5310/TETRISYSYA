#pragma once
#include "UIDrawer.h"
#include "Header.h"


class Tetris
{
public:
    Tetris(UIDrawer& ui);
    ~Tetris();

    void restart();
    void timerUpdate();
    void repaint();

    bool keyPress(int key);
    void pause(bool paused);
    bool isGameOver();

private:
    UIDrawer& _ui;
    bool _isPaused;

    int timertick = 0;
    wchar_t timetext[99999];
};

