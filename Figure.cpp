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

void Figure::changeRotation(int rotationCount)
{

}

void Figure::blocks(POINT* apt)
{
    for (int i = 0; i < FiguresSet::BLOCKS_NUMBER; i++)
        apt[i] = _body[i];
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