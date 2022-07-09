#pragma once
#include <windows.h>

class Figure
{
public:
	Figure(COLORREF pieceColor, POINT* blocks);
	~Figure();

	void changeRotation();
	void blocks(POINT* apt);
	int bottom(POINT* apt);

	COLORREF color();
	int width();
	int height();

private:
	COLORREF _color;
	POINT* _body;

	int _rotation;

	bool hasPointAt(int x, int y);
};

