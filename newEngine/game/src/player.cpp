#include "player.hpp"
Player::Player(const char *name)
{
	Sprite::name = name;
	makeAnimation("test", 1, 100, "idle");
}

Player::~Player()
{
}

void Player::update()
{
	Sprite::update();
	Animation::update();
	Movement::update();
	//test();
}
void Player::test()
{
	printf("asdf");
}
