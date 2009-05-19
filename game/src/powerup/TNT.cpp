#include <boost/shared_ptr.hpp>

#include "../sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "TNT.hpp"

RegisterPowerup RegisterTNT("TNT");

TNT::TNT(genericSprite *owner)
	:	genericPowerUp(owner)
{
}

TNT::~TNT()
{
}

void TNT::onActionKey()
{
}

void TNT::update()
{
}
