#include "FlagCOunter.h"

FlagCounter::FlagCounter(int num) {
	setSprite("digits");  // this is math used to make the counter 
	getSprite().setTextureRect(sf::IntRect((num * 21), 0, 21, 32));
}
