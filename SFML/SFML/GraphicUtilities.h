#pragma once
#include "SFML/Graphics.hpp"
#include <string>
class GraphicUtilities
{
public: 
	//Initialize sprite with it's texture. 
	static void InitializeSprite(sf::Sprite &spriteToInitialize, sf::Texture &textureToInitialize, const std::string imageAddress);
	static void InitializeSprite(sf::Sprite &spriteToInitialize, sf::Texture &textureToInitialize, const std::string imageAddress,sf::IntRect rect);
};

