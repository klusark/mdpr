#include <Poco/SharedPtr.h>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "chute.hpp"

RegisterPowerup RegisterChute("chute");

Chute::Chute(GenericSprite *owner)
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
