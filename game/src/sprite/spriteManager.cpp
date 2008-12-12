#include "spriteManager.hpp"
#include "genericSprite.hpp"
#include "player.hpp"
#include <map>

spriteManager::spriteManager()
{
	Player *player1 = new Player;
	registerSprite(player1);
}

spriteManager::~spriteManager()
{
}

void spriteManager::registerSprite(genericSprite *sprite)
{
	Sprites["asfd"] = sprite;
	return;
}

void spriteManager::update()
{
	spriteContainer::iterator iter;
	for( iter = spriteManager::Sprites.begin(); iter != spriteManager::Sprites.end(); ++iter ) {
		genericSprite *tempSprite = iter->second;
		tempSprite->update();
		tempSprite->draw(tempSprite->getX(), tempSprite->getY());

	}
}

