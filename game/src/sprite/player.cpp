#include <SFML/Graphics/Image.hpp>

#include "player.hpp"
#include "genericSprite.hpp"
#include "../network/packets.hpp"
#include "../crc.hpp"

sf::Image Player::Image;

Player::Player(const std::string &name) : genericSprite(name, "player", Image)
{
	spriteType = player;
	CRC crc;
	changeAnimation(crc.stringToShort("run"));
	keyMap[keyLeft]		= false;
	keyMap[keyRight]	= false;

	SetX(50);

	setYVelocity(30.0f);


}

Player::~Player()
{
}

void Player::update()
{
	float velocity = (float)(-1*keyMap[keyLeft]+keyMap[keyRight])*30;
	setXVelocity(velocity);
	genericSprite::update();
}
