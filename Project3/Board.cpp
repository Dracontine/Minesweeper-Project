#include "Board.h"
using namespace std;

Board::Board() {
	continueGame = true;
	debugMode = false; // parent cosntructor
	testGame = false;
}
	float one = 0.0f;void Board::tilePos(Tile(&t)[16][25]) {

	float y = 0.0f;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			t[i][j].setPos(one, y);
			one += 32.0f;
		}
		one = 0;
		y += 32.0f;
	}
}
void Board::drawBoardTile(sf::RenderWindow& window, Tile(&t)[16][25], Mine(&m)[50], vector<Mine>& testMines, vector<numberOfMinesNear>& nums, vector<Flag>& flags, vector<FlagCounter>& counters, vector<Button>& buttons, bool continueGame, bool debugMode, bool testMode) {
	int index = 0;
	if (continueGame && !testMode) {    //draws the board tiles on the board
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 25; j++) {
				index = minePos(t[i][j], m);
				if (index != -1 && t[i][j].isRevealed()) {
					window.draw(t[i][j].getSprite());
					window.draw(m[index].getSprite());

				}
				else {
					window.draw(t[i][j].getSprite());
					for (int k = 0; k < nums.size(); k++) {
						if (t[i][j].isRevealed()) {
							if (nums[k].tile.getPosition().x == t[i][j].tile.getPosition().x && nums[k].tile.getPosition().y == t[i][j].tile.getPosition().y) {
								window.draw(nums[k].getSprite());
							}
						}
					}
				}
			}
		}
		if (dubzzzzCheck(t, m, flags)) {
			window.draw(buttons[2].getSprite());
		}
		if (!dubzzzzCheck(t, m, flags)) {
			window.draw(buttons[0].getSprite());
		}

	}
	if (testMode) { //drws the first test board

		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 25; j++) {
				index = minePosTests(t[i][j], testMines);
				if ((index != -1 && debugMode) || (index != -1 && !continueGame)) {
					window.draw(t[i][j].getSprite());
					window.draw(testMines[index].getSprite());
				}
				else if (index != -1 && !debugMode) {
					window.draw(t[i][j].getSprite());
				}
				else {
					window.draw(t[i][j].getSprite());
					for (int k = 0; k < nums.size(); k++) {
						if (t[i][j].isRevealed()) {
							if (nums[k].tile.getPosition().x == t[i][j].tile.getPosition().x && nums[k].tile.getPosition().y == t[i][j].tile.getPosition().y) {
								window.draw(nums[k].getSprite());
							}
						}
					}
				}
			}
		}
		if (continueGame && !duBskies(t, testMines, flags)) {
			window.draw(buttons[0].getSprite());
		}
		if (continueGame && duBskies(t, testMines, flags)) {
			window.draw(buttons[2].getSprite());
		}
		if (!continueGame) {
			window.draw(buttons[1].getSprite());
		}
	}
	if ((!continueGame || debugMode) && !testMode) {
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 25; j++) {
				index = minePos(t[i][j], m);
				if (index != -1) {
					window.draw(t[i][j].getSprite());
					window.draw(m[index].getSprite());
				}
				else {
					window.draw(t[i][j].getSprite());
					for (int k = 0; k < nums.size(); k++) {
						if (t[i][j].isRevealed()) {
							if (nums[k].tile.getPosition().x == t[i][j].tile.getPosition().x && nums[k].tile.getPosition().y == t[i][j].tile.getPosition().y) {
								window.draw(nums[k].getSprite());
							}
						}
					}
				}
			}
		}
		if (!continueGame)
			window.draw(buttons[1].getSprite());
		if (dubzzzzCheck(t, m, flags)) {
			window.draw(buttons[2].getSprite());
		}

	}
	for (int i = 0; i < flags.size(); i++) {
		window.draw(flags[i].getSprite());
	}

	if (flags.size() <= 50) {    //flags size

		index = 50 - flags.size(); 
		counters[0].setPos(0, 512);
		window.draw(counters[0].getSprite());
		counters[index / 10].setPos(21, 512);
		window.draw(counters[index / 10].getSprite());
		counters[index % 10].setPos(42, 512);
		window.draw(counters[index % 10].getSprite());
	}
	else if (flags.size() > 50) {
		counters[10].setPos(0, 512);
		window.draw(counters[10].getSprite());
		index = flags.size() - 50;
		if (index >= 100) {
			counters[index / 100].setPos(21, 512);
			window.draw(counters[index / 100].getSprite());
			counters[(index / 10) % 10].setPos(42, 512);
			window.draw(counters[(index / 10) % 10].getSprite());
			counters[index % 10].setPos(63, 512);
			window.draw(counters[index % 10].getSprite());
		}
		else {
			counters[0].setPos(21, 512);
			window.draw(counters[0].getSprite());
			counters[index / 10].setPos(42, 512);
			window.draw(counters[index / 10].getSprite());
			
			counters[index % 10].setPos(63, 512); 
			window.draw(counters[index % 10].getSprite());
		}
	}


	window.draw(buttons[3].getSprite());
	window.draw(buttons[4].getSprite());
	window.draw(buttons[5].getSprite());
	window.draw(buttons[6].getSprite());

}
void Board::setBoard(std::vector<numberOfMinesNear>& numbers, std::vector<Flag>& flags, Tile(&t)[16][25], Mine(&m)[50]) {
	numbers.clear();
	flags.clear();
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			t[i][j].resetBoardTile();
		}
	}
	setPostionMine(t, m);
	numberstoMine(numbers, t);
	start();
}
void Board::numberstoMine(vector<numberOfMinesNear>& nums, Tile(&t)[16][25]) {
	int count = 0;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			count = t[i][j].adjMinesPos();
			if (count != 0) {
				if (!t[i][j].mineHereCheck()) {
					numberOfMinesNear n(count);
					n.setPos(t[i][j].tile.getPosition().x, t[i][j].tile.getPosition().y);
					nums.push_back(n);
				}
			}
		}
	}
}
void Board::setPostionMine(Tile(&t)[16][25], Mine(&m)[50]) {
	vector<int> randomx;
	vector<int> randomY;
	for (int i = 0; i < 50; i++) { // generates 50 random width and height numbers
		int height = TilePlacement::integerForMines(0, 15);
		randomY.push_back(height);
		int width = TilePlacement::integerForMines(0, 24);
		randomx.push_back(width);
	}
	if (mineDupes(randomx, randomY)) {
		randomx.clear();
		randomY.clear();
		setPostionMine(t, m);
	}
	else {
		for (int i = 0; i < 50; i++) {
			m[i].setPos(t[randomY[i]][randomx[i]].tile.getPosition().x, t[randomY[i]][randomx[i]].tile.getPosition().y);
			t[randomY[i]][randomx[i]].setMine();
		}
	}
}
int Board::minePos(Tile(&t), Mine(&m)[50]) {
	for (int i = 0; i < 50; i++) {
		if (t.tile.getPosition().x == m[i].tile.getPosition().x && t.tile.getPosition().y == m[i].tile.getPosition().y) {
			return i;
		}
	}
	return -1;
}
//checks the psotions of mines and makes sure there only one per tile
int Board::minePosTests(Tile& t, vector<Mine>& testMines) {
	for (int i = 0; i < testMines.size(); i++) {
		if (t.tile.getPosition().x == testMines[i].tile.getPosition().x && t.tile.getPosition().y == testMines[i].tile.getPosition().y) {
			return i;
		}
	}
	return -1;
}
bool Board::mineDupes(vector<int>& randWidth, vector<int>& randHeight) { 
	for (int i = 0; i < randHeight.size(); i++) {
		for (int j = i + 1; j < randHeight.size(); j++) {
			if (randHeight[i] == randHeight[j] && i != j) {
				if (randWidth[i] == randWidth[j]) {
					return true;
				}
			}
		}
	}
	return false;
}
void Board::tileLink(Tile(&t)[16][25]) {  //links to tile locations to mines and flags

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			if (i == 0) {
				t[i][j].adjacents[0] = nullptr;
				t[i][j].adjacents[1] = nullptr;
				t[i][j].adjacents[7] = nullptr;
				if (j == 0) {
					t[i][j].adjacents[2] = &t[0][1];
					t[i][j].adjacents[3] = &t[1][1];
					t[i][j].adjacents[4] = &t[1][0];
					t[i][j].adjacents[5] = nullptr;
					t[i][j].adjacents[6] = nullptr;
				}
				if (j != 0 && j != 24) {
					t[i][j].adjacents[2] = &t[i][j + 1];
					t[i][j].adjacents[3] = &t[i + 1][j + 1];
					t[i][j].adjacents[4] = &t[i + 1][j];
					t[i][j].adjacents[5] = &t[i + 1][j - 1];
					t[i][j].adjacents[6] = &t[i][j - 1];
				}
				if (j == 24) {
					t[i][j].adjacents[6] = &t[i][j - 1];
					t[i][j].adjacents[5] = &t[i + 1][j - 1];
					t[i][j].adjacents[4] = &t[i + 1][j];
					t[i][j].adjacents[2] = nullptr;
					t[i][j].adjacents[3] = nullptr;
				}
			}
			else if (i != 0 && i != 15) { 
				if (j == 0) {
					t[i][j].adjacents[0] = &t[i - 1][j];
					t[i][j].adjacents[1] = &t[i - 1][j + 1];
					t[i][j].adjacents[2] = &t[i][j + 1];
					t[i][j].adjacents[3] = &t[i + 1][j + 1];
					t[i][j].adjacents[4] = &t[i + 1][j];
					t[i][j].adjacents[5] = nullptr;
					t[i][j].adjacents[6] = nullptr;
					t[i][j].adjacents[7] = nullptr;
				}
				else if (j == 24) {
					t[i][j].adjacents[0] = &t[i - 1][j];
					t[i][j].adjacents[1] = nullptr;
					t[i][j].adjacents[2] = nullptr;
					t[i][j].adjacents[3] = nullptr;
					t[i][j].adjacents[4] = &t[i + 1][j];
					t[i][j].adjacents[5] = &t[i + 1][j - 1];
					t[i][j].adjacents[6] = &t[i][j - 1];
					t[i][j].adjacents[7] = &t[i - 1][j - 1];
				}
				else if (j != 0 && j != 24) {
					t[i][j].adjacents[0] = &t[i - 1][j];
					t[i][j].adjacents[1] = &t[i - 1][j + 1];
					t[i][j].adjacents[2] = &t[i][j + 1];
					t[i][j].adjacents[3] = &t[i + 1][j + 1];
					t[i][j].adjacents[4] = &t[i + 1][j];
					t[i][j].adjacents[5] = &t[i + 1][j - 1];
					t[i][j].adjacents[6] = &t[i][j - 1];
					t[i][j].adjacents[7] = &t[i - 1][j - 1];
				}
			}
			else if (i == 15) { 
				t[i][j].adjacents[3] = nullptr;
				t[i][j].adjacents[4] = nullptr;
				t[i][j].adjacents[5] = nullptr;
				if (j == 0) {
					t[i][j].adjacents[2] = &t[i][j + 1];
					t[i][j].adjacents[1] = &t[i - 1][j + 1];
					t[i][j].adjacents[0] = &t[i - 1][j];
					t[i][j].adjacents[6] = nullptr;
					t[i][j].adjacents[7] = nullptr;
				}
				if (j != 0 && j != 24) {
					t[i][j].adjacents[0] = &t[i - 1][j];
					t[i][j].adjacents[1] = &t[i - 1][j + 1];
					t[i][j].adjacents[2] = &t[i][j + 1];
					t[i][j].adjacents[6] = &t[i][j - 1];
					t[i][j].adjacents[7] = &t[i - 1][j - 1];

				}
				if (j == 24) {
					t[i][j].adjacents[0] = &t[i - 1][j];
					t[i][j].adjacents[7] = &t[i - 1][j - 1];
					t[i][j].adjacents[6] = &t[i][j - 1];
					t[i][j].adjacents[2] = nullptr;
					t[i][j].adjacents[1] = nullptr;
				}
			}
		}
	}
}
void Board::addFlag(std::vector<Flag>& flags, Tile& t) {
	Flag f;
	f.setPos(t.tile.getPosition().x, t.tile.getPosition().y);
	flags.push_back(f);
	t.setFlagDownHere();
}
void Board::removeFlag(std::vector<Flag>& flags, Tile& t) {
	for (int i = 0; i < flags.size(); i++) {
		if (flags[i].tile.getPosition().x == t.tile.getPosition().x && flags[i].tile.getPosition().y == t.tile.getPosition().y) {
			flags.erase(flags.begin() + i);

		}
	}
	t.removeFlag();
}
void Board::counterMake(std::vector<FlagCounter>& counters) {
	for (int i = 0; i <= 10; i++) {
		FlagCounter c(i);
		counters.push_back(c);
	}
}
void Board::buttonCreation(std::vector<Button>& buttons) {
	// creates the buttons on the  bottom by making a vector
	Button a("face_happy");
	a.setPosition(368, 512);
	Button b("face_lose");
	b.setPosition(368, 512);
	Button c("face_win");
	c.setPosition(368, 512);
	Button d("debug");
	d.setPosition(496, 512);
	Button e("test_1");
	e.setPosition(560, 512);
	Button f("test_2");
	f.setPosition(624, 512);
	Button g("test_3");
	g.setPosition(688, 512);
	buttons.push_back(a);
	buttons.push_back(b);
	buttons.push_back(c);
	buttons.push_back(d);
	buttons.push_back(e);
	buttons.push_back(f);
	buttons.push_back(g);
}
void Board::start() {
	this->continueGame = true;
}
void Board::endGame() {
	this->continueGame = false;
}
bool Board::update() {
	return this->continueGame;
}
void Board::setTest(bool b) {
	this->testGame = b;
}
bool Board::getTest() {
	return this->testGame;
}
void Board::loadTest(ifstream& f, Tile(&t)[16][25], Mine(&m)[50], vector<Mine>& mines, const char* name, char(&binData)[16][25], std::vector<numberOfMinesNear>& numbers, std::vector<Flag>& flags) {
	f.open(name);
	int i = 0;
	mines.clear();
	numbers.clear();
	flags.clear();
	vector<Tile> mineTiles;
	string line;
	int count = 0;
	while (getline(f, line, '\n')) {
		for (i = 0; i < 25; i++) {
			binData[count][i] = line[i];
		}
		count++;
	}
	for (i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			t[i][j].resetBoardTile();
			if (binData[i][j] == '1') {
				t[i][j].setMine();
				mineTiles.push_back(t[i][j]);
			}
		}
	}
	for (i = 0; i < mineTiles.size(); i++) {
		Mine mn;
		mn.tile.setPosition(mineTiles[i].tile.getPosition().x, mineTiles[i].tile.getPosition().y);
		mines.push_back(mn);

	}
	numberstoMine(numbers, t);
	mineTiles.clear();
}
void Board::setDebugger(bool debug) {
	this->debugMode = debug;
}
bool Board::getDebugger() {
	return this->debugMode;
}
bool Board::duBskies(Tile(&t)[16][25], vector<Mine>& testMines, vector<Flag>& flags) {
	int mineCount = 0;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			if (t[i][j].isRevealed() && minePosTests(t[i][j], testMines) == -1) {
				mineCount++;
			}
		}
	}
	if (mineCount == 400 - testMines.size()) {
		flags.clear();
		for (int i = 0; i < testMines.size(); i++) {
			Flag flagHere;
			flagHere.setPos(testMines[i].getSprite().getPosition().x, testMines[i].getSprite().getPosition().y);
			flags.push_back(flagHere);
		}
		return true;
	}
	else {
		return false;
	}
}
bool Board::dubzzzzCheck(Tile(&t)[16][25], Mine(&m)[50], vector<Flag>& flags) {
	int countMine = 0;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			if (t[i][j].isRevealed() && minePos(t[i][j], m) == -1) {
				countMine++;
			}
		}
	}
	if (countMine == 350) {
		flags.clear();
		for (int i = 0; i < 50; i++) {
			Flag flagHere;
			flagHere.setPos(m[i].getSprite().getPosition().x, m[i].getSprite().getPosition().y);
			flags.push_back(flagHere);
		}
		return true;
	}
	else {
		return false;
	}
}