#pragma once
#include "Block.h"

class Figure
{
	Block figure[4];

public:
	Figure(int(&Cords)[2][4]);

	~Figure();
};

