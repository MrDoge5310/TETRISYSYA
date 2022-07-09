#include "Figure.h"
#include "FiguresSet.h"

Figure::Figure(COLORREF pieceColor, POINT* blocks)
{
    _body = new POINT[FiguresSet::BLOCKS_NUMBER];
    _color = pieceColor;
    _rotation = 0;

    POINT leftBottomPoint = blocks[0];

    for (int i = 1; i < FiguresSet::BLOCKS_NUMBER; i++)
    {
        leftBottomPoint.x = min(blocks[i].x, leftBottomPoint.x);
        leftBottomPoint.y = min(blocks[i].y, leftBottomPoint.y);
    }

    for (int i = 0; i < FiguresSet::BLOCKS_NUMBER; i++)
    {
        _body[i].x = blocks[i].x - leftBottomPoint.x;
        _body[i].y = blocks[i].y - leftBottomPoint.y;
    }
}

Figure::~Figure()
{
    delete[] _body;
}

void Figure::changeRotation(POINT* points)
{
    for (int i = 0; i < FiguresSet::BLOCKS_NUMBER; i++)
    {
        points[i].x = -_body[i].y;
        points[i].y = _body[i].x;
    }
}

void Figure::blocks(POINT* points)
{
    for (int i = 0; i < FiguresSet::BLOCKS_NUMBER; i++)
        points[i] = _body[i];
}

int Figure::bottom(POINT* points)
{
    int count = 0;
    for (int x = 0; x < width(); x++)
    {
        for (int y = 0; y < height(); y++)
        {
            if (hasPointAt(x, y))
            {
                points[count].x = x;
                points[count].y = y;
                count++;

                break;
            }
        }
    }
    return count;
}

int Figure::left(POINT* points)
{
    int i = 0;
    for (int y = 0; y < height(); y++)
    {
        for (int x = 0; x < height(); x++)
        {
            if (hasPointAt(x, y))
            {
                points[i].x = x;
                points[i].y = y;
                i++;
                break;
            }
        }
    }
    return i;
}

int Figure::right(POINT* points)
{
    int i = 0;
    for (int y = 0; y < height(); y++)
    {
        for (int x = width() - 1; x >= 0; x--)
        {
            if (hasPointAt(x, y))
            {
                points[i].x = x;
                points[i].y = y;
                i++;
                break;
            }
        }
    }
    return i;
}

COLORREF Figure::color()
{
    return _color;
}

int Figure::width()
{
    int result = 0;
    for (int i = 0; i < FiguresSet::BLOCKS_NUMBER; i++)
    {
        result = max((int)_body[i].x + 1, result);
    }
    return result;
}

int Figure::height()
{
    int result = 0;
    for (int i = 0; i < FiguresSet::BLOCKS_NUMBER; i++)
    {
        result = max((int)_body[i].y + 1, result);
    }
    return result;
}

bool Figure::hasPointAt(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        if (_body[i].x == x && _body[i].y == y)
            return true;
    }
    return false;
}