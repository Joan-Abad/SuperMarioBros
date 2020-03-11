#include "GraphicUtilities.h"
#include <iostream>

//Initialize sprite with it's texture.  
void GraphicUtilities::InitializeSprite(sf::Sprite & spriteToInitialize, sf::Texture & textureToInitialize, const std::string imageAddress)
{
	if (textureToInitialize.loadFromFile(imageAddress))
		spriteToInitialize.setTexture(textureToInitialize);
	else
		std::cerr << std::endl << imageAddress << " wasn't loaded correctly, please check address. ";
	
}

void GraphicUtilities::InitializeSprite(sf::Sprite & spriteToInitialize, sf::Texture & textureToInitialize, const std::string imageAddress, sf::IntRect IntRect)
{
	if (textureToInitialize.loadFromFile(imageAddress, IntRect))
		spriteToInitialize.setTexture(textureToInitialize);
	else
		std::cerr << std::endl << imageAddress << " wasn't loaded correctly, please check address. ";}
