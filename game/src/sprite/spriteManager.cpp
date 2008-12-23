#include "spriteManager.hpp"
#include "genericSprite.hpp"
#include "player.hpp"
#include <map>
#include <boost/shared_ptr.hpp>

boost::shared_ptr<spriteManager> sprite;

spriteManager::spriteManager(bool server) : active(false), server(server)
{
	//Player *player1 = ;
	boost::shared_ptr<genericSprite> player(new Player("player1", server));
	registerSprite(player);
}

spriteManager::~spriteManager()
{
}

void spriteManager::registerSprite(boost::shared_ptr<genericSprite> sprite)
{
	Sprites[sprite->name] = sprite;
	return;
}

void spriteManager::registerSprite(std::string type, std::string name)
{
	if (type.compare("player") == 0){
		boost::shared_ptr<genericSprite> player(new Player(name, server));
		Sprites[name] = player;
	}else{
		std::cout << "Could not find sprite type" << std::endl;
	}
}

void spriteManager::update()
{
	spriteContainer::iterator iter;
	for( iter = spriteManager::Sprites.begin(); iter != spriteManager::Sprites.end(); ++iter ) {
		boost::shared_ptr<genericSprite> tempSprite = iter->second;
		tempSprite->update();
	}
}
void spriteManager::draw()
{
    spriteContainer::iterator iter;
	for( iter = spriteManager::Sprites.begin(); iter != spriteManager::Sprites.end(); ++iter ) {
		boost::shared_ptr<genericSprite> tempSprite = iter->second;
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
