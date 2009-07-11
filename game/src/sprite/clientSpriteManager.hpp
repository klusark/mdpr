#ifndef clientSpriteManager_hpp
#define clientSpriteManager_hpp

#include <map>
#include <string>

#include <Poco/SharedPtr.h>
#include <Poco/Mutex.h>

#include "clientSprite.hpp"
#include "network/packets.hpp"

class ClientSpriteManager
{
public:
	ClientSpriteManager();
	~ClientSpriteManager();

	typedef std::map<unsigned short, Poco::SharedPtr<ClientSprite> > spriteContainer;
	spriteContainer Sprites;

	typedef std::map<unsigned short, Poco::SharedPtr<sf::Image> > imageContainer;
	imageContainer Images;

	typedef std::map<unsigned short, animationCreationPacket> animationPacketContainer;
	animationPacketContainer Animations;

	void registerSprite(Poco::SharedPtr<ClientSprite> sprite);
	void update();
	void draw(sf::RenderWindow &App);
	bool isActive();
	void setActive(bool toggle);
	void removeSprite(unsigned int spriteID);
	void removeSprite(std::string spriteID);
	Poco::Mutex spriteMutex;

private:
    bool active;
	
	
};

extern Poco::SharedPtr<ClientSpriteManager> sprite;


#endif // #ifndef clientSpriteManager_hpp
