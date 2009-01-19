#ifndef spriteManager_hpp
#define spriteManager_hpp

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include "spriteCollision.hpp"

#include "genericSprite.hpp"

class spriteManager
{
public:
	spriteManager(bool server = false);
	~spriteManager();
	typedef std::map<unsigned short, boost::shared_ptr<genericSprite> > spriteContainer;

	spriteContainer Sprites;
	void registerSprite(boost::shared_ptr<genericSprite> sprite);
	void update();
	void draw(sf::RenderWindow &App);
	bool isActive();
	void setActive(bool toggle);
	void removeSprite(unsigned int spriteID);
	boost::mutex spriteMutex;
	spriteCollision collision;
private:
    bool active;
	bool server;
	
	
};

#ifndef SERVER
extern spriteManager sprite;
#endif

#endif //spriteManager_hpp
