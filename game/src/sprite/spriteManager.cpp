#include "spriteManager.hpp"
#include "genericSprite.hpp"
#include "player.hpp"
#include <map>

spriteManager::spriteManager() : active(false)
{
	//Player *player1 = ;
	registerSprite(new Player("player1"));
}

spriteManager::~spriteManager()
{
	for(spriteContainer::iterator it = Sprites.begin(); it != Sprites.end(); ++it){
		delete it->second;
	}
}

void spriteManager::registerSprite(genericSprite *sprite)
{
	Sprites[sprite->name] = sprite;
	return;
}

void spriteManager::registerSprite(std::string type, std::string name)
{
	if (type.compare("player") == 0){
		registerSprite(new Player(name));
	}else{
		std::cout << "Could not find sprite" << std::endl;
	}
}

void spriteManager::update()
{
	spriteContainer::iterator iter;
	for( iter = spriteManager::Sprites.begin(); iter != spriteManager::Sprites.end(); ++iter ) {
		genericSprite *tempSprite = iter->second;
		tempSprite->update();
	}
}
void spriteManager::draw()
{
    spriteContainer::iterator iter;
	for( iter = spriteManager::Sprites.begin(); iter != spriteManager::Sprites.end(); ++iter ) {
		genericSprite *tempSprite = iter->second;
		tempSprite->draw(tempSprite->getX(), tempSprite->getY());
	}

}

bool spriteManager::isActive()
{
    return active;
}

void spriteManager::setActive(bool toggle)
{
    active = toggle;
}
