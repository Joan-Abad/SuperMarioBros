#pragma once
#include <vector>
#include "Actor.h"

class Map
{
public: 
	Map();

private: 
	std::vector<Actor*> allActorsOnMap;

public: 
	std::vector<Actor*> &getAllActorsOnMap() { return allActorsOnMap; };
	void DrawAllActors(sf::RenderWindow &window);
};

