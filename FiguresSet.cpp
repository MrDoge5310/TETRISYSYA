#include "FiguresSet.h"
#include "stdlib.h"

FiguresSet::FiguresSet() 
{
	figures[0] = new Figure();
	figures[1] = new Figure();
	figures[2] = new Figure();
	figures[3] = new Figure();
	figures[4] = new Figure();
}

FiguresSet::~FiguresSet()
{
	for (int i = 0; i < FIGURES_COUNT; i++)
		if (figures[i] != 0)
			delete figures[i];
}

Figure* FiguresSet::getRandomFigure()
{
	int index = rand() % FIGURES_COUNT;
	return figures[index];
}