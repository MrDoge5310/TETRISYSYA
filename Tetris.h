#pragma once
#include "UIDrawer.h"
#include "FiguresSet.h"

class Tetris
{
public:
    Tetris(UIDrawer& ui, int width, int height, int speed);
    ~Tetris();

    void restart();
    int timerUpdate();
    void repaint();

    bool moveFigure(int x, int y);
    void rotateFigure();

    void pause(bool paused);
    bool isPaused();

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
    
    bool putFigure(int x, int y);
    bool putToTop();
    bool CheckColisionBottom();
    bool CheckColisionLeft();
    bool CheckColisionRight();
    void clearPrevFigurePosition();

    int clearFilledRows();
    void dropRows(int y);
    bool isFullFilled(int y);
    void isGameOver();

    int _width;
    int _height;
    int _speed;
    int _score;
    int _targetScore;

    int _currentX;
    int _currentY;

    int _currentSpeed;
    bool _isPaused;
    bool _isGameOver = false;
};

