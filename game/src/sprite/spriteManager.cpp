#include <boost/crc.hpp>
#include <boost/shared_ptr.hpp>

#include <SFML/Graphics.hpp>

#include <map>
#include <sstream>
#include <string>
#include <iostream>

#include "genericSprite.hpp"
#include "player.hpp"
#include "spriteManager.hpp"

boost::shared_ptr<spriteManager> sprite;

spriteManager::spriteManager(bool server) : active(false), server(server)
{
	//Player *player1 = ;
	boost::shared_ptr<genericSprite> player(new Player("player1"));
	 
	registerSprite(player);
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
	Sprites[atoi(buf.str().c_str())] = sprite;
}

void spriteManager::registerSprite(std::string type, std::string name)
{
	if (type.compare("player") == 0){
		/*boost::shared_ptr<genericSprite> player(new Player(name, server));

		boost::crc_16_type  result;
		result.process_bytes(name.c_str(), name.length());
		std::stringstream buf;
		buf << result.checksum();

		Sprites[atoi(buf.str().c_str())] = player;*/
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

void spriteManager::draw(sf::RenderWindow &App)
{
    spriteContainer::iterator iter;
	for( iter = spriteManager::Sprites.begin(); iter != spriteManager::Sprites.end(); ++iter ) {
		//boost::shared_ptr<genericSprite> tempSprite = iter->second;
		App.Draw(*iter->second.get());//tempSprite->draw(tempSprite->getX(), tempSprite->getY());
		
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
