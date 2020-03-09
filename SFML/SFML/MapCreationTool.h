#pragma once
#include "SFML/Graphics.hpp"
#include "Actor.h"
#include <vector>
#include "Map.h"

struct Entity
{
	sf::Sprite spr_Entity;
	sf::Texture tex_Entity;
};

class MapCreationTool
{

public: 
	MapCreationTool(sf::RenderWindow & window);

private: 

	//Mouse
	sf::RectangleShape mouseDetection; 

//Tool Box
	//Graphics
	sf::RectangleShape toolBox;
	sf::Vector2f toolBoxSize; 
	
	//Letters
	sf::Text text_Actors;
	sf::Font font_Actors;
	
	//Actors available to Spawn
	Entity CoinBlock; 


	//All entities must be stores here. 
	std::vector<Entity> AllEntities;
	std::vector<Entity*> EntitiesInWorld;

	bool LeftMouseButtonPressed = false; 

	Actor * actorSpawned = nullptr; 

public: 
	void ShowMapCreationTool(sf::RenderWindow &window);
	void HandleInput(sf::RenderWindow &window, Map & map);
};

