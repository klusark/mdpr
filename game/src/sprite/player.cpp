#include <SFML/Graphics/Image.hpp>

#include "player.hpp"
#include "genericSprite.hpp"

sf::Image Player::Image;

Player::Player(const std::string &name) : genericSprite(name, "player", Image)
{

	changeAnimation("run");

}

Player::~Player()
{
}

