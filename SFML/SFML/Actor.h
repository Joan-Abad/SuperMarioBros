#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "MapCreationTool.h"

class MapCreationTool;
extern enum EntityType;

class Actor
{
public: 
	Actor() = default;
	Actor(std::string spriteImageAddress, EntityType actorTypeConst);
	
	EntityType actorType;

//Getters
	//Get actor sprite
	sf::Sprite &getSprite() { return spr_actor; };

protected: 
	//Graphics
	sf::Sprite spr_actor; 
	sf::Texture tex_actor; 
};

