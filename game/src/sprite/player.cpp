#include <SFML/Graphics/Image.hpp>

#include "player.hpp"
#include "genericSprite.hpp"
#include "../network/packets.hpp"

sf::Image Player::Image;

Player::Player(const std::string &name) : genericSprite(name, "player", Image)
{

	changeAnimation("run");
	keyMap[keyLeft]		= false;
	keyMap[keyRight]	= false;


}

Player::~Player()
{
}

void Player::update()
{
	float velocity = (float)(-1*keyMap[keyLeft]+keyMap[keyRight])*60;
	setXVelocity(velocity);
	genericSprite::update();
}
