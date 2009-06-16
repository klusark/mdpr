#include "platform.hpp"
#include "genericSprite.hpp"

Platform::Platform(const std::string &name)
	:	genericSprite(name, "platform")
{

	changeAnimation("platform");
	spriteType = platformType;
	currentState = aliveState;
}

Platform::~Platform()
{
}
