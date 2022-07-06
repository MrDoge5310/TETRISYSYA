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

void Tetris::keyPress(int key)
{
    if (key != VK_PAUSE && key != VK_RETURN && _isPaused)
        return;

    switch (key)
    {
    case VK_UP:
        //rrottate
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
        //pause
        break;
    case VK_RETURN:
        // restart?
        break;
    }
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

    if (_currentFigure == NULL)
        createNewFigure();

    clearFilledRows();
    _currentSpeed = max(_speed - 1, 100); // todo add correct speed logic
    _score += 1; // todo add sleared lines multiplier

    if (CheckColision() == true)
    {
        putFigure(_currentX, _currentY);

        _currentFigure = _figures.getRandomFigure();
        putToTop();

    }
    else moveFigure(0, -1);

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

void Tetris::createNewFigure() 
{
    _currentFigure = _figures.getRandomFigure();
    putFigure(4, _height - 1);
}

bool Tetris::moveFigure(int x, int y) 
{
        int newX = _currentX + x;
        int newY = _currentY + y;

        if (newX < 0 || newY < 0)
            return false;


        return putFigure(newX, newY);
}

bool Tetris::CheckColision()
{
    int c = 0;

    COLORREF black = RGB(0, 0, 0);
    POINT blocks[FiguresSet::BLOCKS_NUMBER];
    _currentFigure->blocks(blocks);
    int mx = 0;
    int my = 0;
    for (int i = 0; i < 4; i++) {
        if (blocks[i].x > mx)
            mx = blocks[i].x;
        if (blocks[i].y > my)
            my = blocks[i].y;
    }
    if (_height - _currentY == _height) {
        return true;
    }

    for (int i = 0; i < 4; i++) {
        if (blocks[i].x == mx || blocks[i].y == my) {
            if (_board[_currentX + blocks[i].x][_currentY - blocks[i].y + 1] != black) {
                return true;
            }
        }
    }

    //return true;
}

bool Tetris::putFigure(int x, int y) 
{
    clearPrevFigurePosition();

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
    POINT blocks[FiguresSet::BLOCKS_NUMBER];
    _currentFigure->blocks(blocks);

    int x, y;
    for (int i = 0; i < FiguresSet::BLOCKS_NUMBER; i++) {
        x = _currentX + blocks[i].x;
        y = _currentY + blocks[i].y;
        if (x > _width - 1 || y > _height - 1)
            continue;
        _board[_currentX + blocks[i].x][_currentY + blocks[i].y] = RGB(0, 0, 0);
    }
}

void Tetris::clearFilledRows()
{
    //_board[i][j] = black;
}


bool Tetris::isGameOver()
{
    // todo add logic
    return false;
}
