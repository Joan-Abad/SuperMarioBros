#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player(std::string imageAddress);


private: 

	//Gravity
	int gravity = 2;
	const int initialGravity;
	bool canMoveRight = true;
	bool canMoveLeft = true;

	bool movingLeft = false;
	bool movingRight = false;

	//Collisions
	sf::RectangleShape collision_Right;
	sf::RectangleShape collision_Left;
	sf::RectangleShape collision_Up;
	sf::RectangleShape collision_Down;

	//Clock

	sf::Clock clockRun;
	sf::Time timerRun;

	void adjustCollisions();

public: 
	void HandlePlayerInput();
	void PlayerMovement();
	void DrawPlayer(sf::RenderWindow &window);
	void CheckPlayerCollisions(std::vector<Actor*> allActorsOnMap);

};

