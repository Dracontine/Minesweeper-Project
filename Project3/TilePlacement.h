#pragma once
#include <random>
class TilePlacement
{
	static std::mt19937 random;
public:
	static int integerForMines(int min, int max);
	static float floatVarMines(float min, float max);
};

