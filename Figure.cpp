#include "Figure.h"

Figure::Figure(int (& Cords)[2][4])
{

	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 4; j++){
			if (i == 0) {
				figure[j].x = Cords[i][j];
			}else
				figure[j].y = Cords[i][j];
		}
	}
}

Figure::~Figure()
{

}