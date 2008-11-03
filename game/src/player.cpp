#include "player.hpp"
Player::Player(const char *name)
{
	Sprite::name = name;
	makeAnimation("run", 4, 100, "run0", "run1", "run2", "run3");
	changeAnimation("run");
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
