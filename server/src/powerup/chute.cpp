#include <Poco/SharedPtr.h>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "chute.hpp"

RegisterPowerup RegisterChute("chute");

Chute::Chute(genericSprite *owner)
	:	genericPowerUp(owner)
{
}

Chute::~Chute()
{
}

void Chute::onActionKey()
{
}

void Chute::update()
{
}
