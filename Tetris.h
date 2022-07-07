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
    COLORREF _black;
    FiguresSet _figures;
    Figure* _currentFigure;

    void newBoard();
    void deleteBoard();
    void drawBoard();

    void createNewFigure();
    bool moveFigure(int x, int y);
    bool putFigure(int x, int y);
    bool putToTop();
    bool CheckColisionBottom();
    void clearPrevFigurePosition();

    int clearFilledRows();
    void dropRows(int y);
    bool isFullFilled(int y);
    bool isGameOver();

    int _width;
    int _height;
    int _speed;
    int _score;
    int _targetScore = 300;

    int _currentX;
    int _currentY;

    int _currentSpeed;
    bool _isPaused;
};

