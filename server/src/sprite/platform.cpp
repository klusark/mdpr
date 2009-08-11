#include "platform.hpp"
#include "genericSprite.hpp"

GenericSprite::collidesWithContainer Platform::colidesWith;

Platform::Platform(const std::string &name)
	:	GenericSprite(name, "platform")
{

	changeAnimation("platform");
	spriteType = platformType;
	currentState = aliveState;
}

Platform::~Platform()
{
}
