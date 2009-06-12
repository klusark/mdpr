#include <SFML/Graphics/Image.hpp>

#include "platform.hpp"
#include "genericSprite.hpp"


sf::Image Platform::Image;

Platform::Platform(const std::string &name)
	:	genericSprite(name, "platform", Image)
{

	changeAnimation("platform");
	spriteType = platformType;
	currentState = aliveState;
}

Platform::~Platform()
{
}
