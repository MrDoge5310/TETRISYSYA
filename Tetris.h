#pragma once
#include "UIDrawer.h"
#include "FiguresSet.h"

class Tetris
{
public:
    Tetris(UIDrawer& ui, int width, int height, int speed);
    ~Tetris();

    void restart();
    void timerUpdate();
    void repaint();

    void keyPress(int key);
    void pause(bool paused);

private:
    UIDrawer& _ui;
    COLORREF** _board;
    FiguresSet _figures;
    Figure* _currentFigure;
    Figure* _nextFigure;

    void newBoard();
    void deleteBoard();
    void drawBoard();

    bool moveFigure(int x, int y);
    bool putFigure(int x, int y);
    bool putToTop();
    bool CheckColision();
    void clearPrevFigurePosition();

    void clearFilledRows();
    bool isGameOver();

    int _width;
    int _height;
    int _speed;
    int _score;

    int _currentX;
    int _currentY;

    int _currentSpeed;
    bool _isPaused;
};

