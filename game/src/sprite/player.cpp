#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "player.hpp"
#include "genericSprite.hpp"

Player::Player() : genericSprite("data/mdpr/sprites/player/player.xml")
{
	//CL_ResourceManager *resources = new CL_ResourceManager();
	run = new CL_Sprite("run", resources);
	this->set_image_data(*run);
}

Player::~Player()
{
}
