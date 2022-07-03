#include "FiguresSet.h"
#include "stdlib.h"

FiguresSet::FiguresSet() 
{
	POINT blocks[BLOCKS_NUMBER]; // temporary storege for block positions

	// Square - dark blue
	blocks[0].x = 0;    blocks[0].y = 0;
	blocks[1].x = 1;    blocks[1].y = 0;
	blocks[2].x = 0;    blocks[2].y = 1;
	blocks[3].x = 1;    blocks[3].y = 1;
	figures[0] = new Figure(RGB(20, 100, 200), blocks);

	// L - green
	blocks[0].x = 0;    blocks[0].y = 0;
	blocks[1].x = 1;    blocks[1].y = 0;
	blocks[2].x = 0;    blocks[2].y = 1;
	blocks[3].x = 1;    blocks[3].y = 1;
	figures[1] = new Figure(RGB(120, 200, 80), blocks);

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