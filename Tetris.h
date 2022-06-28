#pragma once
#include "UIDrawer.h"

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
};

