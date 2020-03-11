#include "Actor.h"
#include "GraphicUtilities.h"



Actor::Actor(std::string spriteImageAddress, EntityType actorTypeConst) : actorType(actorTypeConst)
{
	GraphicUtilities::InitializeSprite(spr_actor, tex_actor, spriteImageAddress);
}

