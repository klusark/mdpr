#include "Mass.hpp"

Mass::Mass(GameManager *gm) : Sprite(gm)
{
	this->gm = gm;
}

Mass::~Mass()
{
}

void Mass::update()
{
	Sprite::update();
	applyGravity();
	checkPlatformCollision();
}

void Mass::applyGravity()
{

}

void Mass::checkPlatformCollision()
{
}