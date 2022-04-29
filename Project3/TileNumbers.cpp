#include "TileNumbers.h"

numberOfMinesNear::numberOfMinesNear(int num) {
	// this just gets the list of numbers that show how many mines are near the tile.
	if (num == 1)
		setSprite("number_1");
	if (num == 2)
		setSprite("number_2");
	if (num == 3)
		setSprite("number_3");
	if (num == 4)
		setSprite("number_4");
	if (num == 5)
		setSprite("number_5");
	if (num == 6)
		setSprite("number_6");
	if (num == 7)
		setSprite("number_7");
	if (num == 8)
		setSprite("number_8");
}
