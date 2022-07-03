#pragma once
#include <windows.h>

class Figure
{
public:
	Figure(COLORREF pieceColor, POINT* blocks);
	~Figure();

	void changeRotation(int rotationCount);
	void blocks(POINT* apt);
	COLORREF color();
	int width();
	int height();

private:
	COLORREF _color;
	POINT* _body;

	int _rotation;
};

