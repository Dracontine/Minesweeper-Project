#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Mine.h"
#include "TilePlacement.h"
#include "TileNumbers.h"
#include "MineFlag.h"
#include "FlagCOunter.h"
#include "Button.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>

class Board         // the board header that is basically the foundation of the project.
{
	bool continueGame;
	bool debugMode;
	bool testGame;
public:
	Board();
	void setBoard(std::vector<numberOfMinesNear>&, std::vector<Flag>&, Tile(&t)[16][25], Mine(&m)[50]);
	void tilePos(Tile(&t)[16][25]);
	void drawBoardTile(sf::RenderWindow& window, Tile(&t)[16][25], Mine(&m)[50], std::vector<Mine>&, std::vector<numberOfMinesNear>&, std::vector<Flag>&, std::vector<FlagCounter>&, std::vector<Button>&, bool, bool, bool);
	void tileLink(Tile(&t)[16][25]);
	bool update();
	void buttonCreation(std::vector<Button>&); // creates buttons
	void counterMake(std::vector<FlagCounter>&);
	void start();
	void endGame();
	void setTest(bool b);
	bool getTest();
	void loadTest(std::ifstream&, Tile(&t)[16][25], Mine(&m)[50], std::vector<Mine>&, const char* name, char(&binData)[16][25], std::vector<numberOfMinesNear>& numbers, std::vector<Flag>& flags);
	void setDebugger(bool);
	bool getDebugger();
	void setPostionMine(Tile(&t)[16][25], Mine(&m)[50]);
	bool mineDupes(std::vector<int>& randWidth, std::vector<int>& randHeight);
	int minePos(Tile(&t), Mine(&m)[50]);
	int minePosTests(Tile(&t), std::vector<Mine>&);
	void numberstoMine(std::vector<numberOfMinesNear>&, Tile(&t)[16][25]);
	void addFlag(std::vector<Flag>&, Tile(&t));  //flag properties
	void removeFlag(std::vector<Flag>&, Tile(&t));
	bool duBskies(Tile(&t)[16][25], std::vector<Mine>&, std::vector<Flag>&); //win conditioins
	bool dubzzzzCheck(Tile(&t)[16][25], Mine(&m)[50], std::vector<Flag>&);
};