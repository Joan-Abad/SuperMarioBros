#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player(std::string imageAddress);


private: 

	//Gravity
	int gravity = 0;
	const int initialGravity;
	bool canMoveRight = true;
	bool canMoveLeft = true;

	//Collisions
	sf::RectangleShape collision_Right;
	sf::RectangleShape collision_Left;
	sf::RectangleShape collision_Up;
	sf::RectangleShape collision_Down;

	void adjustCollisions();

public: 
	void HandlePlayerInput();
	void PlayerMovement();
	void DrawPlayer(sf::RenderWindow &window);
	void CheckPlayerCollisions(std::vector<Actor*> allActorsOnMap);

};

