#pragma once
#include "UIDrawer.h"



class Tetris
{
public:
    Tetris(UIDrawer& ui);
    ~Tetris();

    void restart();
    void timerUpdate(HWND hTimer);
    void repaint();

    bool keyPress(int key);
    void pause(bool paused);
    bool isGameOver();

private:
    UIDrawer& _ui;
    bool _isPaused;
    double timertick = 0;
    int realtime = 1;

    //HDC hdcTimer;
    //RECT timerRect = { 550, 600, 100, 20 };
};

