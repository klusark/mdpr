#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include <SFML/Graphics.hpp>

#include <map>
#include <sstream>
#include <string>
#include <iostream>
#include "../crc.hpp"
#include "genericSprite.hpp"
#include "player.hpp"
#include "spriteCollision.hpp"
#include "spriteManager.hpp"

#ifndef SERVER
spriteManager sprite;
#endif

spriteManager::spriteManager(bool server)
	:	active(false),
		server(server),
		collision(Sprites)
{
}

spriteManager::~spriteManager()
{
}

void spriteManager::registerSprite(boost::shared_ptr<genericSprite> sprite)
{
	CRC crc;
	boost::mutex::scoped_lock lock(spriteMutex);
	Sprites[crc.stringToShort(sprite->name)] = sprite;
}

void spriteManager::update()
{
	boost::mutex::scoped_lock lock(spriteMutex);
	collision.before();
	spriteContainer::iterator iter;
	for(iter = Sprites.begin(); iter != Sprites.end(); ++iter){
		iter->second->update();
		collision.update(iter->first);
	}
}

void spriteManager::draw(sf::RenderWindow &App)
{
	boost::mutex::scoped_lock lock(spriteMutex);
    spriteContainer::iterator iter;
	for(iter = Sprites.begin(); iter != Sprites.end(); ++iter){
		
		App.Draw(*iter->second.get());
		
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
