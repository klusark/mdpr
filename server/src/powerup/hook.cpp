#include <boost/shared_ptr.hpp>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "hook.hpp"

RegisterPowerup RegisterHook("hook");

Hook::Hook(genericSprite *owner)
	:	genericPowerUp(owner)
{
}

Hook::~Hook()
{
}

void Hook::onActionKey()
{
}

void Hook::update()
{
}
