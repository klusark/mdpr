#include <Poco/SharedPtr.h>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "puck.hpp"

RegisterPowerup RegisterPuck("puck");

Puck::Puck(GenericSprite *owner)
	:	genericPowerUp(owner)
{
}

Puck::~Puck()
{
}

void Puck::onActionKey()
{
}

void Puck::update()
{
}
