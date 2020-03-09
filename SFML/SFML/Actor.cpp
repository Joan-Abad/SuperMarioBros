#include "Actor.h"
#include "GraphicUtilities.h"

Actor::Actor(std::string spriteImageAddress)
{
	GraphicUtilities::InitializeSprite(spr_actor, tex_actor, spriteImageAddress);
}

bool Actor::CheckActorCollision(Actor & ActorColliding)
{
	//If actor is colliding with the other actor
	if(spr_actor.getGlobalBounds().intersects(ActorColliding.getSprite().getGlobalBounds()))
		return true; 

	else
		return false;
}
