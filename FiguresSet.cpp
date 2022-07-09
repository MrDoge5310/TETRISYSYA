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
	figures[0] = new Figure(RGB(0, 0, 150), blocks);

	// L - green
	blocks[0].x = 0;    blocks[0].y = 0;
	blocks[1].x = 0;    blocks[1].y = 1;
	blocks[2].x = 0;    blocks[2].y = 2;
	blocks[3].x = 1;    blocks[3].y = 2;
	figures[1] = new Figure(RGB(0, 200, 0), blocks);

	//I - yellow
	blocks[0].x = 0;    blocks[0].y = 0;
	blocks[1].x = 0;    blocks[1].y = 1;
	blocks[2].x = 0;    blocks[2].y = 2;
	blocks[3].x = 0;    blocks[3].y = 3;
	figures[2] = new Figure(RGB(255, 255, 0), blocks);

	//T - red
	blocks[0].x = 1;    blocks[0].y = 0;
	blocks[1].x = 1;    blocks[1].y = 1;
	blocks[2].x = 0;    blocks[2].y = 1;
	blocks[3].x = 1;    blocks[3].y = 2;
	figures[3] = new Figure(RGB(200, 0, 0), blocks);

	//S - pink
	blocks[0].x = 2;    blocks[0].y = 0;
	blocks[1].x = 1;    blocks[1].y = 0;
	blocks[2].x = 1;    blocks[2].y = 1;
	blocks[3].x = 0;    blocks[3].y = 1;
	figures[4] = new Figure(RGB(255, 0, 127), blocks);

}

FiguresSet::~FiguresSet()
{
	for (int i = 0; i < FIGURES_COUNT; i++)
		if (figures[i] != 0)
			delete figures[i];
}

Figure* FiguresSet::getRandomFigure()
{
	srand(time(0));
	int index = rand() % FIGURES_COUNT;
	return figures[index];
}