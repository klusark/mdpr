#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "player.hpp"

Player::Player() : CL_Sprite()
{
	CL_ResourceManager *resources = new CL_ResourceManager("data/mdpr/sprites/player/player.xml");
	run = new CL_Sprite("run", resources);
	this->set_image_data(*run);
}

Player::~Player()
{
}
