#include "FontUtilities.h"
#include <iostream>

void FontUtilities::InitializeText(sf::Text & text, sf::Font & font, const std::string textAddress)
{
	if (font.loadFromFile(textAddress))
		text.setFont(font);
	else
		std::cerr << std::endl << textAddress << " font wasn't found.";

}
