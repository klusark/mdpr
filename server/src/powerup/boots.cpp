#include <boost/shared_ptr.hpp>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "boots.hpp"

RegisterPowerup RegisterBoots("boots");

Boots::Boots(genericSprite *owner)
	:	genericPowerUp(owner)
{
}

Boots::~Boots()
{
}

void Boots::onActionKey()
{
}

void Boots::update()
{
}
