#include "Block.h"

RECT Block::CreateRect()
{
	RECT r;
	r = { this->x+ 30, this->y + 30, this->x, this->y };

	return r;
}

Block::~Block()
{
}