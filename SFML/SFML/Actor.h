#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class Actor
{
public: 
	Actor(std::string spriteImageAddress);

//Getters
	//Get actor sprite
	sf::Sprite &getSprite() { return spr_actor; };
	bool CheckActorCollision(Actor &ActorColliding);
private: 

	//Graphics
	sf::Sprite spr_actor; 
	sf::Texture tex_actor; 
};

