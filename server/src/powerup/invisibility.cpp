#include <Poco/SharedPtr.h>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "invisibility.hpp"

RegisterPowerup RegisterInvisibility("invisibility");

Invisibility::Invisibility(genericSprite *owner)
	:	genericPowerUp(owner)
{
}

Invisibility::~Invisibility()
{
}

void Invisibility::onActionKey()
{
}

void Invisibility::update()
{
}
