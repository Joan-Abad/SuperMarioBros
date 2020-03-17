#include "Player.h"
#include <iostream>

Player::Player(std::string imageAddress) : Character(imageAddress), initialGravity(gravity)
{
//Collisions
	//LEFT
	collision_Left.setSize(sf::Vector2f(10, 64));
	collision_Left.setFillColor(sf::Color::Transparent);
	
	//RIGHT
	collision_Right.setSize(sf::Vector2f(10, 64));
	collision_Right.setFillColor(sf::Color::Transparent);

	//UP
	collision_Up.setSize(sf::Vector2f(64, 10));
	collision_Up.setFillColor(sf::Color::Blue);

	//DOWN
	collision_Down.setSize(sf::Vector2f(64, 10));
	collision_Down.setFillColor(sf::Color::Red);
}

void Player::adjustCollisions()
{
	//Right
	collision_Right.setPosition(spr_actor.getPosition().x + tex_actor.getSize().x - 10, spr_actor.getPosition().y);

	//Left
	collision_Left.setPosition(spr_actor.getPosition().x, spr_actor.getPosition().y);

	//Up
	collision_Up.setPosition(spr_actor.getPosition().x, spr_actor.getPosition().y - collision_Up.getSize().y + 10);

	//Down
	collision_Down.setPosition(spr_actor.getPosition().x, spr_actor.getPosition().y + tex_actor.getSize().y - 10);

	
}

void Player::HandlePlayerInput()
{


	//Player movement left, right
	PlayerMovement();
}

void Player::PlayerMovement()
{
	spr_actor.move(0, float(gravity));


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		movingLeft = true;
		spr_actor.move(movementSpeed * -1, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		movingLeft = true;
		spr_actor.move(movementSpeed, 0);
	}

	adjustCollisions();
}

void Player::DrawPlayer(sf::RenderWindow & window)
{
	window.draw(spr_actor);
	window.draw(collision_Left);
	window.draw(collision_Right);
	window.draw(collision_Down);
	window.draw(collision_Up);
}

void Player::CheckPlayerCollisions(std::vector<Actor*> allActorsOnMap)
{
	for (auto actorOnMap : allActorsOnMap)
	{
		if (collision_Down.getGlobalBounds().intersects(actorOnMap->getSprite().getGlobalBounds()))
		{
			//std::cout << "\nPlayer Colliding bottom part";
			gravity = 0; 
			break;
		}
		else
		{
			gravity = initialGravity;
		}
	}
}
