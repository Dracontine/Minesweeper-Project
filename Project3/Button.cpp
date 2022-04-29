#include "Button.h"
#include "TextureManager.h"
using namespace std;

Button::Button(const char* name) {  //makes buttons on the bottom
	setSprite(name);
}
void Button::setSprite(const char* name) {
	this->image.setTexture(TextureManager::getTextureInfo(name));
}
sf::Sprite& Button::getSprite() {
	return this->image;
}
void Button::setPosition(float width, float height) {
	this->getSprite().setPosition(width, height);
}

