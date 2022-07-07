#include "Tetris.h"
#include "UIDrawer.h"

Tetris::Tetris(UIDrawer& ui, int width, int height, int speed) : _ui(ui)
{
    _width = width;
    _height = height;
    _speed = speed;
    _currentSpeed = speed;
    _targetScore = 300;
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

void Tetris::keyPress(int key)
{
    if (key != VK_PAUSE && key != VK_RETURN && _isPaused)
        return;

    switch (key)
    {
    case VK_UP:
        //rottate
        break;
    case VK_DOWN:
        moveFigure(0, -1);
        break;
    case VK_LEFT:
        moveFigure(-1, 0);
        break;
    case VK_RIGHT:
        moveFigure(1, 0);
        break;
    case VK_SPACE:
        //rotate
        break;
    case VK_PAUSE:
        if (!_isPaused)
            pause(true);
        else
            _isPaused = false;
    case VK_RETURN:
        restart();
        break;
    }
}

void Tetris::timerUpdate()
{
    if (_isPaused)
        return;

    if (_isGameOver)
    {
        //_isPaused = true;
        _ui.drawGameOver();
        return;
    }

    


    if (_currentFigure == NULL)
        createNewFigure();
    
    if (moveFigure(0, -1) == false)
    {
        _score += clearFilledRows()/2 * 100;
        if (_score >= _targetScore) {
            _currentSpeed =  max(50, _speed - 50);
            _targetScore *= 2;
        }

        isGameOver();
        createNewFigure();
    }
    
    // todo add time calculation
    repaint();
}

void Tetris::pause(bool paused)
{
    if (_isGameOver)
        return;

    _isPaused = paused;
    if (paused)
        _ui.drawPause();
}

void Tetris::repaint()
{
    _ui.drawInterface();
    _ui.drawSpeed((500 - _currentSpeed) / 2, _width + 1, 12);
    _ui.drawScore(_score, _width + 1, 13);

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
    for (int i = 0; i < _width; i++)
        for (int j = 0; j < _height; j++)
            _ui.drawBlock(i, j, _board[i][j]);
}

void Tetris::createNewFigure() 
{
    _currentFigure = _figures.getRandomFigure();
    putFigure(4, _height - 1);
}

bool Tetris::moveFigure(int x, int y) 
{
    if (CheckColisionBottom())
    {
        return false;
    }

    // todo add chech colisions for left and right side

    clearPrevFigurePosition();

    int newX = _currentX + x;
    int newY = _currentY + y;

    if (newX < 0 || newY < 0)
        return false;


    return putFigure(newX, newY);
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
    int cleardRaws = 0;
    for (int y = 0; y < _height; y++)
    {
        if (isFullFilled(y) == true) {
            dropRows(y);
            cleardRaws++;
        }
    }
    return cleardRaws;
    cleardRaws = 0;
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
