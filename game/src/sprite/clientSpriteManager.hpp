#ifndef clientSpriteManager_hpp
#define clientSpriteManager_hpp

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include "clientSprite.hpp"

class ClientSpriteManager
{
public:
	ClientSpriteManager();
	~ClientSpriteManager();

	typedef std::map<unsigned short, boost::shared_ptr<ClientSprite> > spriteContainer;
	spriteContainer Sprites;

	typedef std::map<unsigned short, boost::shared_ptr<sf::Image> > imageContainer;
	imageContainer Images;

	void registerSprite(boost::shared_ptr<ClientSprite> sprite);
	void update();
	void draw(sf::RenderWindow &App);
	bool isActive();
	void setActive(bool toggle);
	void removeSprite(unsigned int spriteID);
	void removeSprite(std::string spriteID);
	boost::mutex spriteMutex;

private:
    bool active;
	
	
};

extern ClientSpriteManager sprite;


#endif // #ifndef clientSpriteManager_hpp
