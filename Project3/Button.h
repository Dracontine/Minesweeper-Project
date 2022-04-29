#pragma once
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
class Button
{
public:  //gets all the textures from the package
	Button(const char* name);
	sf::Sprite image;
	void setSprite(const char* name);
	void setPosition(float width, float height);
	sf::Sprite& getSprite();

};



