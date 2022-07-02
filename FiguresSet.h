#pragma once
#include "Figure.h"

class FiguresSet
{
public:
	// Constants
	enum { FIGURES_COUNT = 5 };

	FiguresSet();
	~FiguresSet();


	Figure* getRandomFigure();
private:
	const int figuresCount = 5;

	Figure *figures[FIGURES_COUNT];
};

