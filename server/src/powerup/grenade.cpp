#include <Poco/SharedPtr.h>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "grenade.hpp"

RegisterPowerup RegisterGrenade("grenade");

Grenade::Grenade(GenericSprite *owner)
	:	genericPowerUp(owner)
{
}

Grenade::~Grenade()
{
}

void Grenade::onActionKey()
{
}

void Grenade::update()
{
}
