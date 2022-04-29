#include <iostream>
#include <fstream>
#include <unordered_map>
#include "TextureManager.h"
#include "TilePlacement.h"
#include "Mine.h"
#include "Board.h"
#include "MineFlag.h"
#include "FlagCOunter.h"
#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
    sf::RenderWindow screenClear(sf::VideoMode(800, 600), "Madhav's Minesweeper"); 
    Board board;       

    Tile tiles[16][25];
    sf::Event event;
    Mine mines[50];
    vector<Mine> mineson123;
    vector<numberOfMinesNear> flooders;
    vector<Flag> flags;
    vector<FlagCounter> counters;
    vector<Button> buttons;
    board.buttonCreation(buttons);
    board.counterMake(counters);
    board.tilePos(tiles);
    board.tileLink(tiles);
    board.setPostionMine(tiles, mines);
    board.numberstoMine(flooders, tiles);
    ifstream unotest;
    ifstream dostest;
    ifstream trestest;
    int testNum = 0;
    char binData[16][25];


    while (screenClear.isOpen())
    {
        while (screenClear.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                screenClear.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    sf::Vector2f clickerLocation = screenClear.mapPixelToCoords(sf::Mouse::getPosition(screenClear));
                    for (int i = 0; i < 16; i++) {
                        for (int j = 0; j < 25; j++) {
                            if (tiles[i][j].tile.getGlobalBounds().contains(clickerLocation) && !tiles[i][j].checkIfFLag() && board.update()) {
                                tiles[i][j].revealTile();
                                if (tiles[i][j].mineHereCheck()) {
                                    board.endGame();

                                }
                                else {
                                    tiles[i][j].revealMinePos();
                                }

                            }
                        }
                    }
                    if (buttons[1].getSprite().getGlobalBounds().contains(clickerLocation)) {
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
                        
                        board.setBoard(flooders, flags, tiles, mines);
                        board.setTest(false);
                        unotest.close();
                        dostest.close();
                        trestest.close();
                        testNum = 0;
                    }
                    else if (buttons[3].getSprite().getGlobalBounds().contains(clickerLocation) && !board.getDebugger()) {
                        board.setDebugger(true);
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
                    else if (buttons[3].getSprite().getGlobalBounds().contains(clickerLocation) && board.getDebugger()) {
                        board.setDebugger(false);
                    }
                    else if (buttons[4].getSprite().getGlobalBounds().contains(clickerLocation)) {
                        board.setTest(true);
                        board.start();
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
                        dostest.close();
                        trestest.close();
                        board.loadTest(unotest, tiles, mines, mineson123, "../boards/testboard1.brd", binData, flooders, flags);

                    }
                    else if (buttons[5].getSprite().getGlobalBounds().contains(clickerLocation)) {
                        board.setTest(true);
                        board.start();
                        bool canic = true;     ///was debugging here
                        while (!canic) {
                            int x = 0;
                            for (int i = 0; i < 30; i++) {
                                x = i;
                                //cout << x;
                                if (x == 23)
                                {
                                    canic = false;
                                    break;

                                }
                            }

                        }
                        unotest.close();
                        trestest.close();
                        board.loadTest(dostest, tiles, mines, mineson123, "../boards/testboard2.brd", binData, flooders, flags);

                    }
                    else if (buttons[6].getSprite().getGlobalBounds().contains(clickerLocation)) {
                        board.setTest(true);
                        board.start();
                        unotest.close();
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
                        dostest.close();
                        board.loadTest(trestest, tiles, mines, mineson123, "../boards/testboard3.brd", binData, flooders, flags);
                    }
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    sf::Vector2f mousePos = screenClear.mapPixelToCoords(sf::Mouse::getPosition(screenClear));
                    bool can = true;
                    while (can == true) {


                        for (int i = 0; i < 16; i++) {
                            for (int j = 0; j < 25; j++) {
                                if (tiles[i][j].tile.getGlobalBounds().contains(mousePos) && !tiles[i][j].checkIfFLag() && !tiles[i][j].isRevealed() && board.update()) {
                                    board.addFlag(flags, tiles[i][j]);
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
                                else if (tiles[i][j].tile.getGlobalBounds().contains(mousePos) && !tiles[i][j].isRevealed() && tiles[i][j].checkIfFLag() && board.update()) {
                                    board.removeFlag(flags, tiles[i][j]);
                                }
                            }
                        }
                        can = false;
                    }
                }
                break;

            }
        }
        screenClear.clear();
        board.drawBoardTile(screenClear, tiles, mines, mineson123, flooders, flags, counters, buttons, board.update(), board.getDebugger(), board.getTest());
        screenClear.display();
    }
    TextureManager::Clear();
    return 0;
}
