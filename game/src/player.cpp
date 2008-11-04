#include "engine/engineAll.hpp"
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
/**
 * test
 */
void Player::update()
{
	Sprite::update();
	Animation::update();
	Movement::update();
	Mass::update();
	Collision::update();
	Input::update();
	//test();
}
void Player::test()
{
	printf("asdf");
}
