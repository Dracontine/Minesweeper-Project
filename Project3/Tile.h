#pragma once
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

class Tile
{  //tile components which check if the thing has a lag mine empty square with number allat information will be shown here.
	bool mineLoc;
	bool shown;
	bool flagHere;
	int mineNear;
public:
	Tile* adjacents[8];
	Tile();
	sf::Sprite tile;
	sf::Sprite& getSprite();
	void setSprite(const char* name);
	void setPos(float x, float y);
	void revealTile();
	void setMine();
	bool mineHereCheck();
	bool isRevealed();
	int adjMinesPos();
	void revealMinePos();
	void setFlagDownHere();
	bool checkIfFLag();
	void removeFlag();
	void resetBoardTile();
};

