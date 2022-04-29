#pragma once
#include <unordered_map>
#include <string>
#include "SFML/Graphics.hpp"

class TextureManager
{
	static std::unordered_map<std::string, sf::Texture> textures;  
	static void LoadTexture(const char* fileName); //gets the texture infos and extracts it





public:
	static sf::Texture& getTextureInfo(const char* name_);
	static void Clear();
};

