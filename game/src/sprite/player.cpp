#include <SFML/Graphics/Image.hpp>

#include "player.hpp"
#include "genericSprite.hpp"

sf::Image Player::Image;

Player::Player(const std::string &name) : genericSprite(name, Image)
{
	//Image = sf::Image();
	//CL_ResourceManager *resources = new CL_ResourceManager();
	//run = new CL_Sprite("run", resources);
	//if (!server){

	//	loadAnimation("run");
	//	changeAnimation("run");
	//}
	//sf::Image Image.LoadFromFile("data/mdpr/sprites/player/run.PNG");
	//sf::Image().LoadFromFile("data/mdpr/sprites/player/run.PNG")
	//Image
	//SetImage(Image);
}

Player::~Player()
{
}

