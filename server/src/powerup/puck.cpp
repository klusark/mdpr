#include <boost/shared_ptr.hpp>

#include "../sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "puck.hpp"

RegisterPowerup RegisterPuck("puck");

Puck::Puck(genericSprite *owner)
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
