#include "Map.h"

Map::Map()
{

}

void Map::DrawAllActors(sf::RenderWindow & window)
{
	for (auto actor : allActorsOnMap)
	{
		window.draw(actor->getSprite());
	}
}
