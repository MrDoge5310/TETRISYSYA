#pragma once
#include <windows.h>

class Figure
{
public:
	Figure(COLORREF pieceColor, POINT* blocks);
	~Figure();

	void changeRotation(POINT* points);
	void blocks(POINT* points);

	int bottom(POINT* points);
	int left(POINT* points);
	int right(POINT* points);

	COLORREF color();
	int width();
	int height();

private:
	COLORREF _color;
	POINT* _body;

	int _rotation;

	bool hasPointAt(int x, int y);
};

