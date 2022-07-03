#include "FiguresSet.h"
#include "stdlib.h"

FiguresSet::FiguresSet() 
{
	figures[0] = new Figure(LfigureCords);
	figures[1] = new Figure(TfigureCords);
	figures[2] = new Figure(SfigureCords);
	figures[3] = new Figure(lfigureCords);
	figures[4] = new Figure(SQfigureCords);
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