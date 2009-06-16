#include <boost/shared_ptr.hpp>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "grenade.hpp"

RegisterPowerup RegisterGrenade("grenade");

Grenade::Grenade(genericSprite *owner)
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
