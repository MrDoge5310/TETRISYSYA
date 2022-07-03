#pragma once
#include "Figure.h"

class FiguresSet
{
public:
	// Constants
	enum { FIGURES_COUNT = 5 };

	FiguresSet();
	~FiguresSet();
	int LfigureCords[2][4] = { 150, 150, 150, 180, 0, 30, 60, 60};
	int TfigureCords[2][4] = {150, 150, 150, 120, 0, 30, 60, 30};
	int SfigureCords[2][4] = {150, 180, 150, 120, 0, 0, 30, 30};
	int lfigureCords[2][4] = {150, 150, 150, 150, 0, 30, 60, 90};
	int SQfigureCords[2][4] = {150, 180, 150, 180, 0, 0, 30, 30};



	Figure* getRandomFigure();
private:
	const int figuresCount = 5;

	Figure *figures[FIGURES_COUNT];
};

