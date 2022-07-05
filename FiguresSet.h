#pragma once
#include "Figure.h"
#include <ctime>

class FiguresSet
{
public:
	// Constants
	enum { FIGURES_COUNT = 5, BLOCKS_NUMBER = 4};// each figure has 4 blocks

	FiguresSet();
	~FiguresSet();

	Figure* getRandomFigure();
private:
	Figure *figures[FIGURES_COUNT];
};

