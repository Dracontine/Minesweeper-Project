#include "TextureManager.h"
using namespace std;

std::unordered_map<std::string, sf::Texture> TextureManager::textures;
void TextureManager::LoadTexture(const char* fileName) {
	string filePath = "../images/";  // from professor foxes lecture on this
	filePath += fileName;
	filePath += ".png";
	textures[fileName].loadFromFile(filePath);
}
sf::Texture& TextureManager::getTextureInfo(const char* name) {
	if (textures.find(name) == textures.end()) { 
		LoadTexture(name);
	}
	return textures[name];
}
void TextureManager::Clear() { //cleasrs and makes new map
	textures.clear();
}
