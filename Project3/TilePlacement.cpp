#include "TilePlacement.h"
#include <ctime>

std::mt19937 TilePlacement::random(time(0)); 


int TilePlacement::integerForMines(int min, int max) {   // this makes the randomized placements of the mines.
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);
}
float TilePlacement::floatVarMines(float min, float max) {
	std::uniform_real_distribution<float> dist(min, max);
	return dist(random);
}