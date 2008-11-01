#include "player.hpp"
Player::Player(const char *name)
{
	Sprite::name = name;
}

Player::~Player()
{
}

void Player::update()
{
	test();
}
void Player::test()
{
	printf("asdf");
}
