#include "Tile.h"
using namespace std;

Tile::Tile() {
	setSprite("tile_hidden");   //default constructor
	mineLoc = false;
	shown = false;
	flagHere = false;
}
sf::Sprite& Tile::getSprite() { //gets the tile info and sets
	return this->tile;
}
void Tile::setSprite(const char* name) {
	this->tile.setTexture(TextureManager::getTextureInfo(name));
}
void Tile::setPos(float x, float y) {
	this->getSprite().setPosition(x, y);
}
void Tile::revealTile() {
	if (!this->checkIfFLag()) {
		this->setSprite("tile_revealed");
		this->shown = true;
	}

}
void Tile::setMine() {
	this->mineLoc = true;  //this is where the mine locations will be and this runs the flood to see if theres a mine near it
}
bool Tile::mineHereCheck() {   
	if (this->mineLoc) {
		return true;
	}
	else {
		return false;
	}
}
bool Tile::isRevealed() {   //when tile is clicked the location and what is there is shown
	if (this->shown) {
		return true;
	}
	return false;
}
int Tile::adjMinesPos() {  //chekcs around basically a flood method to get mine pos
	int count = 0;
	for (int i = 0; i < 8; i++) {
		if (this->adjacents[i] != nullptr) {
			if (this->adjacents[i]->mineHereCheck())
				count++;
		}
		bool canic = true;
		while (!canic) {
			int x = 0;
			for (int i = 0; i < 30; i++) {
				x = i;
				if (x == 23)
				{
					canic = false;   
					break;

				}
			}

		}
	}
	return count;
}
void Tile::revealMinePos() {  //reveals where the mines will be 
	if (this != nullptr && this->adjMinesPos() == 0 && !this->mineHereCheck() && !this->checkIfFLag()) {
		for (int i = 0; i < 8; i++) {
			if (this->adjacents[i] != nullptr) {
				bool canic = true;
				while (!canic) {
					int x = 0;
					for (int i = 0; i < 30; i++) {
						x = i;
						if (x == 23)
						{
							canic = false;
							break;

						}
					}

				}
				if (!this->adjacents[i]->isRevealed() && !this->adjacents[i]->mineHereCheck() && !this->checkIfFLag()) {
					this->adjacents[i]->revealTile();
					if (this->adjacents[i]->adjMinesPos() == 0) {
						this->adjacents[i]->revealMinePos();
					}
				}
			}
		}

	}
}
void Tile::setFlagDownHere() {
	this->flagHere = true;
}
bool Tile::checkIfFLag() {
	if (this->flagHere) {
		return true;
	}                   

	else {
		return false;
	}


}
void Tile::removeFlag() {
	this->flagHere = false;

}
void Tile::resetBoardTile() {
	this->setSprite("tile_hidden");
	this->shown = false;
	mineLoc = false;
	flagHere = false;
}