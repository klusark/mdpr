#include "helpers.hpp"
#include "sprite/clientSpriteManager.hpp"
#include "clientSprite.hpp"

ClientSprite::ClientSprite(const std::string &name) 
	:	name(name),
		flipped(false)
{

	SetX((unsigned short)-1);
	SetY((unsigned short)-1);
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
