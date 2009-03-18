#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include <SFML/Graphics.hpp>

#include <map>
#include "../helpers.hpp"
#include "genericSprite.hpp"
#include "player.hpp"
#include "spriteCollision.hpp"
#include "spriteManager.hpp"

spriteManager sprite;

spriteManager::spriteManager()
	:	active(false),
		collision(Sprites)
{
}

spriteManager::~spriteManager()
{
}

void spriteManager::registerSprite(boost::shared_ptr<genericSprite> sprite)
{

	boost::mutex::scoped_lock lock(spriteMutex);
	Sprites[stringToCRC(sprite->name)] = sprite;
}

void spriteManager::update()
{
	collision.before();
	spriteContainer::iterator iter;
	for(iter = Sprites.begin(); iter != Sprites.end(); ++iter){
		iter->second->update();
		collision.update(iter->first);
	}
}

void spriteManager::draw(sf::RenderWindow &App)
{
    spriteContainer::iterator iter;
	for(iter = Sprites.begin(); iter != Sprites.end(); ++iter){
		iter->second->draw(App);
		//App.Draw(*iter->second.get());
		
	}
}

void spriteManager::removeSprite(unsigned int spriteID)
{
	spriteContainer::iterator spriteToErase = Sprites.find(spriteID);
	if (spriteToErase != Sprites.end()){
		Sprites.erase(spriteToErase);
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
