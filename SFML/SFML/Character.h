#pragma once
#include "Actor.h"
#include <string>
class Character : public Actor
{
public: 
	Character(const std::string imageAddress);

protected: 
	int life; 
	int damage; 
	float movementSpeed;

public:
};

