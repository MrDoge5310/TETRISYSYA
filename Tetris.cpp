#include "Tetris.h"
#include "UIDrawer.h"

Tetris::Tetris(UIDrawer& ui, int width, int height, int speed) : _ui(ui)
{
    _width = width;
    _height = height;
    _speed = speed;
    _currentSpeed = speed;
    _isPaused = false;
    
    newBoard();
}

Tetris::~Tetris()
{
    deleteBoard();
}

void Tetris::restart()
{
    deleteBoard();
    newBoard();
    _isPaused = false;
    _score = 0;
    _currentSpeed = _speed;

    repaint();
}

bool Tetris::keyPress(int key)
{
    if (key != VK_PAUSE && key != VK_RETURN && _isPaused)
        return false;

    switch (key)
    {
    case VK_UP:
        //move down fast
        break;
    case VK_DOWN:
        //move down
        break;
    case VK_LEFT:
        //move left
        break;
    case VK_RIGHT:
        //move right
        break;
    case VK_SPACE:
        //rotate
        break;
    case VK_PAUSE:
        //pause
        break;
    case VK_RETURN:
        // restart?
        break;
    default:
        return false;
    }
    return true;
}

void Tetris::timerUpdate()
{
    if (_isPaused)
        return;

    if (isGameOver())
    {
        _isPaused = true;
        _ui.drawGameOver();
        return;
    }

    clearFilledRows();
    _currentSpeed = max(_speed - 1, 100); // todo add correct speed logic
    _score += 1; // todo add sleared lines multiplier

    // todo add time calculation
    repaint();
}

void Tetris::pause(bool paused)
{
    if (isGameOver())
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
    else if (isGameOver())
        _ui.drawGameOver();
}

void Tetris::newBoard()
{
    _board = new COLORREF * [_width];
    for (int x = 0; x < _width; x++)
    {
        _board[x] = new COLORREF[_height];
        for (int y = 0; y < _height; y++)
            _board[x][y] = RGB(0, 0, 0);
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

void Tetris::clearFilledRows()
{
    //if (_board[j][i] == RGB(0,0,0))
}


bool Tetris::isGameOver()
{
    // todo add logic
    return false;
}
