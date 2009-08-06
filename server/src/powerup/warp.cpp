#include <Poco/SharedPtr.h>

#include "sprite/genericSprite.hpp"
#include "powerUpManager.hpp"
#include "warp.hpp"

RegisterPowerup RegisterWarp("warp");

Warp::Warp(GenericSprite *owner)
	:	genericPowerUp(owner)
{
}

Warp::~Warp()
{
}

void Warp::onActionKey()
{
}

void Warp::update()
{
}
