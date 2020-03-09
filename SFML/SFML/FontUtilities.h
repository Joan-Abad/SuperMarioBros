#pragma once
#include "GraphicUtilities.h"
#include <string>

class FontUtilities
{
public: 

	static void InitializeText(sf::Text &text, sf::Font & font, const std::string textAddress);
};

