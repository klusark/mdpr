#include "Mass.hpp"

Mass::Mass()
{
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