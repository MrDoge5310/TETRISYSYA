#pragma once
#include "UIDrawer.h"

class Tetris
{
public:
    Tetris(UIDrawer& ui, int width, int height, int speed);
    ~Tetris();

    void restart();
    void timerUpdate();
    void repaint();

    bool keyPress(int key);
    void pause(bool paused);

private:
    UIDrawer& _ui;
    COLORREF** _board;

    void newBoard();
    void deleteBoard();
    void drawBoard();
    void clearFilledRows();
    bool isGameOver();

    int _width;
    int _height;
    int _speed;
    int _score;

    int _currentSpeed;
    bool _isPaused;
};

