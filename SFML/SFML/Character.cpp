#include "Character.h"

Character::Character(const std::string imageAddress) : Actor(imageAddress, NONE)
{
	movementSpeed = 1;
}


