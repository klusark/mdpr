#include "platform.hpp"
#include "genericSprite.hpp"
#include "helpers.hpp"

Platform::Platform(const std::string &name):
GenericSprite(name, "platform")
{

	changeAnimation("platform");
	spriteType = platformType;
	currentState = aliveState;
	getCollidesWith();
	getCollidesWith();
}

Platform::~Platform()
{
}

GenericSprite::collidesWithContainer Platform::getCollidesWith()
{
	static GenericSprite::collidesWithContainer colidesWith;
	static bool test;
	if (!test){
		colidesWith.insert(stringToCRC("test"));
		test = true;
	}
	return colidesWith;
}
