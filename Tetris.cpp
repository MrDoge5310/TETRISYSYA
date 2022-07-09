#include "Tetris.h"
#include "UIDrawer.h"

Tetris::Tetris(UIDrawer& ui, int width, int height, int speed) : _ui(ui)
{
    _width = width;
    _height = height;
    _speed = speed;
    _currentSpeed = speed;
    _targetScore = 200;
    _isPaused = false;
    _black = RGB(0, 0, 0);
    newBoard();
}

Tetris::~Tetris()
{
    deleteBoard();
}

void Tetris::restart()
{
    if (!_isGameOver)
        return;

    deleteBoard();
    newBoard();
    _isGameOver = false;
    _score = 0;
    _currentSpeed = _speed;
    _targetScore = 300;

    repaint();
}

int Tetris::timerUpdate()
{
    if (_isPaused)
        return _currentSpeed;

    if (_isGameOver)
    {
        _ui.drawGameOver();
        return _currentSpeed;
    }

    if (_currentFigure == NULL)
        createNewFigure();
    
    if (moveFigure(0, -1) == false)
    {
        _score += clearFilledRows() * 100;
        if (_score >= _targetScore) {
            _currentSpeed =  max(50, _currentSpeed - 50);
            _targetScore *= 2;
        }

        isGameOver();
        createNewFigure();
    }
    
    repaint();

    return _currentSpeed;
}

void Tetris::pause(bool paused)
{
    if (_isGameOver)
        return;

    _isPaused = paused;
    if (paused)
        _ui.drawPause();
}

bool Tetris::isPaused()
{
    return _isPaused;
}

void Tetris::repaint()
{
    _ui.drawSpeed(_currentSpeed, 1, 23);
    _ui.drawScore(_score, 6, 23);

    drawBoard();

    if (_isPaused)
        _ui.drawPause();
    else if (_isGameOver)
        _ui.drawGameOver();
}

void Tetris::newBoard()
{
    _board = new COLORREF * [_width];
    for (int x = 0; x < _width; x++)
    {
        _board[x] = new COLORREF[_height];
        for (int y = 0; y < _height; y++)
            _board[x][y] = _black;
    }
}

void Tetris::deleteBoard()
{
    for (int i = 0; i < _width; i++)
        delete[] _board[i];
    delete[] _board;
}

void Tetris::drawBoard()
{
    for (int x = 0; x < _width; x++)
        for (int y = 0; y < _height; y++)
            _ui.drawBlock(x, y+2, _board[x][y]);
}

void Tetris::createNewFigure() 
{
    _currentFigure = _figures.getRandomFigure();
    putFigure(4, _height - 1);
}

bool Tetris::moveFigure(int x, int y) 
{
    if (y < 0 && CheckColisionBottom())
    {
        return false;
    }
    if (x < 0 && CheckColisionLeft())
    {
        return false;
    }
    if (x > 0 && CheckColisionRight())
    {
        return false;
    }

    clearPrevFigurePosition();

    int newX = _currentX + x;
    int newY = _currentY + y;

    if (newX < 0 || newY < 0)
        return false;


    return putFigure(newX, newY);
}

void Tetris::rotateFigure()
{
    Figure* tmp = _currentFigure;

    // Figure movement if it need some space
    int disX = max(_currentX + _currentFigure->width() - _width, 0);

    clearPrevFigurePosition();

    POINT blocks[FiguresSet::BLOCKS_NUMBER];
    _currentFigure->changeRotation(blocks);
    _currentFigure = new Figure(_currentFigure->color(), blocks);

    // If rotation successfull
    if (putFigure(_currentX - disX, _currentY))
        return;

    // Undo if not enought space
    _currentFigure = tmp;
    putFigure(_currentX, _currentY);
}

bool Tetris::CheckColisionBottom()
{
    POINT blocks[FiguresSet::BLOCKS_NUMBER];
    int blocksCount = _currentFigure->bottom(blocks);

    int mx = 0;
    int my = 0;
    
    for (int i = 0; i < blocksCount; i++)
    {
        mx = _currentX + blocks[i].x;
        my = _currentY + blocks[i].y;

        if (my < _height && (my == 0 || _board[mx][my - 1] != _black))
            return true;
    }
    return false;
}

bool Tetris::CheckColisionLeft()
{
    POINT blocks[FiguresSet::BLOCKS_NUMBER];
    int blocksCount = _currentFigure->left(blocks);

    int mx = 0;
    int my = 0;

    for (int i = 0; i < blocksCount; i++)
    {
        mx = _currentX + blocks[i].x;
        my = _currentY + blocks[i].y;

        if (my > _height - 1)
            continue;
        if (mx == 0 || _board[mx - 1][my] != _black)
            return true;
    }
    return false;
}

bool Tetris::CheckColisionRight()
{
    POINT blocks[FiguresSet::BLOCKS_NUMBER];
    int blocksCount = _currentFigure->right(blocks);

    int mx = 0;
    int my = 0;

    for (int i = 0; i < blocksCount; i++)
    {
        mx = _currentX + blocks[i].x;
        my = _currentY + blocks[i].y;

        if (my > _height - 1)
            continue;
        if (mx == _width - 1 || _board[mx + 1][my] != _black)
            return true;
    }
    return false;
}

bool Tetris::putFigure(int x, int y) 
{
    if (x + _currentFigure->width() > _width)
        return false;

    _currentX = x;
    _currentY = y;

    POINT blocks[FiguresSet::BLOCKS_NUMBER];
    _currentFigure->blocks(blocks);

    for (int i = 0; i < FiguresSet::BLOCKS_NUMBER; i++)
    {
        if (y + blocks[i].y > _height - 1)
            continue;
        _board[x + blocks[i].x][y + blocks[i].y] = _currentFigure->color();
    }
    return true;
}

bool Tetris::putToTop()
{
    int x = 4;
    int y = _height - 1;

    if (x + _currentFigure->width() > _width)
        return false;

    _currentX = x;
    _currentY = y;

    POINT blocks[FiguresSet::BLOCKS_NUMBER];
    _currentFigure->blocks(blocks);

    for (int i = 0; i < 4; i++)
    {
        if (y + blocks[i].y > _height - 1)
            continue;
        _board[x + blocks[i].x][y + blocks[i].y] = _currentFigure->color();
    }
    return true;
}

void Tetris::clearPrevFigurePosition()
{
    if (_currentFigure == NULL)
        return;

    POINT blocks[FiguresSet::BLOCKS_NUMBER];
    _currentFigure->blocks(blocks);

    int x, y;
    for (int i = 0; i < FiguresSet::BLOCKS_NUMBER; i++) {
        x = _currentX + blocks[i].x;
        y = _currentY + blocks[i].y;
        if (x > _width - 1 || y > _height - 1)
            continue;
        _board[_currentX + blocks[i].x][_currentY + blocks[i].y] = _black;
    }
}

int  Tetris::clearFilledRows()
{
    bool isComplete;
    int cleardRaws = 0;

    for (int y = 0; y < _height; y++)
    {
        if (isFullFilled(y))
        {
            for (int x = 0; x < _width; x++) // clear row
                _board[x][y] = _black;

            for (int my = y; my < _height - 1; my++) // move down rows
            {
                for (int mx = 0; mx < _width; mx++)
                    _board[mx][my] = _board[mx][my + 1];
            }
            y = -1;
            cleardRaws++;
        }
    }
    return cleardRaws;
}

void Tetris::dropRows(int y)
{
    for (int x = 0; x < _width; x++) {
        _board[x][y] = _black;
    }

    for (y; y < _height; y++)
    {
        for (int x = 0; x < _width; x++) {
            _board[x][y] = _board[x][y+1];
        }
    }
}

bool Tetris::isFullFilled(int y)
{
    for (int x = 0; x < _width; x++)
    {
        if (_board[x][y] == _black)
        {
            return false;
        }
    }
    
    return true;
}

void Tetris::isGameOver()
{
    if (_currentY + _currentFigure->height() >= _height)
        _isGameOver = true;
    else
        _isGameOver = false;
}
