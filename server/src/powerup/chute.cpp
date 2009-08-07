#include <Poco/SharedPtr.h>

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
