#include <boost/crc.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include <SFML/Graphics.hpp>

#include <map>
#include <sstream>
#include <string>
#include <iostream>

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
	boost::crc_16_type  result;
	result.process_bytes(sprite->name.c_str(), sprite->name.length());
	std::stringstream buf;
	buf << result.checksum();
	boost::mutex::scoped_lock lock(spriteMutex);
	Sprites[atoi(buf.str().c_str())] = sprite;
}

void spriteManager::registerSprite(std::string type, std::string name)
{
	if (type.compare("player") == 0){
		boost::shared_ptr<genericSprite> player(new Player(name));

		boost::crc_16_type  result;
		result.process_bytes(name.c_str(), name.length());
		std::stringstream buf;
		buf << result.checksum();
		boost::mutex::scoped_lock lock(spriteMutex);
		Sprites[atoi(buf.str().c_str())] = player;
	}else{
		std::cout << "Could not find sprite type" << std::endl;
	}
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

bool spriteManager::isActive()
{
    return active;
}

void spriteManager::setActive(bool toggle)
{
    active = toggle;
}
