#include "Tetris.h"
#include "UIDrawer.h"


Tetris::Tetris(UIDrawer& ui) : _ui(ui)
{
    _isPaused = false;
}

Tetris::~Tetris()
{
}


void Tetris::restart()
{
    _isPaused = false;
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
    timertick++;

    wsprintf(timetext, TEXT("Time: %d"), timertick);
    SetWindowText(hTimer, timetext);

    if (_isPaused)
        return;
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
}

bool Tetris::isGameOver()
{
    return false;
}