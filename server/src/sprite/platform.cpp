#include "platform.hpp"
#include "genericSprite.hpp"

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
