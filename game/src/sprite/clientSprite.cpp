#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <SFML/Graphics/Sprite.hpp>

#include "helpers.hpp"
#include "sprite/clientSpriteManager.hpp"
#include "clientSprite.hpp"

ClientSprite::ClientSprite(const std::string &name) 
	:	name(name),
		timesSkiped(0),
		flipped(false),
		currentState(deadState)
{

	SetX(unsigned short(-1));
	SetY(unsigned short(-1));
}

ClientSprite::~ClientSprite()
{
}

void ClientSprite::update()
{
	SetSubRect(XYWHToLTRB(sprite.Animations[currentAnimationID].startX + (currentFrame * sprite.Animations[currentAnimationID].width) + (currentFrame * sprite.Animations[currentAnimationID].padding), sprite.Animations[currentAnimationID].startY, sprite.Animations[currentAnimationID].width, sprite.Animations[currentAnimationID].height));
	FlipX(flipped);
}

void ClientSprite::draw(sf::RenderWindow &App)
{
	App.Draw(*this);
}
