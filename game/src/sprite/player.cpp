#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "player.hpp"
#include "genericSprite.hpp"

Player::Player(const std::string &name) : genericSprite("data/mdpr/sprites/player/player.xml", name)
{
	//CL_ResourceManager *resources = new CL_ResourceManager();
	//run = new CL_Sprite("run", resources);

	loadAnimation("run");
	changeAnimation("run");

}

Player::~Player()
{
}
