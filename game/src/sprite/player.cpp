#include <SFML/Graphics/Image.hpp>

#include "player.hpp"
#include "genericSprite.hpp"
#include "../network/packets.hpp"
#include "../crc.hpp"
#include "../powerup/gun.hpp"
#include <iostream>

sf::Image Player::Image;

Player::Player(const std::string &name) : genericSprite(name, "player", Image)
{
	spriteType = player;
	CRC crc;
	changeAnimation(crc.stringToShort("run"));
	keyMap[keyLeft]		= false;
	keyMap[keyRight]	= false;
	keyMap[keyAction]	= false;

	SetX(50);

	setYVelocity(30.0f);
	hasPowerUp = true;
	
	currentPowerup = boost::shared_ptr<genericPowerUp>(new Gun(this));


}

Player::~Player()
{
}

void Player::update()
{
	if (keyMap[keyAction] == true && hasPowerUp){
		currentPowerup->onActionKey();
	}
	float velocity = (float)(-1*keyMap[keyLeft]+keyMap[keyRight])*30;
	setXVelocity(velocity);
	currentPowerup->update();
	genericSprite::update();
}
