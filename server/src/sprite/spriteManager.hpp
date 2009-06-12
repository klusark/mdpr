#ifndef spriteManager_hpp
#define spriteManager_hpp

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include "spriteCollision.hpp"

#include "genericSprite.hpp"

#ifdef SERVER
#include "effectManager.hpp"
#endif // #indef SERVER

class spriteManager
{
public:
	spriteManager();
	~spriteManager();
	typedef std::map<unsigned short, boost::shared_ptr<genericSprite> > spriteContainer;

	spriteContainer Sprites;
	void registerSprite(boost::shared_ptr<genericSprite> sprite);
	void update();
	void draw(sf::RenderWindow &App);
	bool isActive();
	void setActive(bool toggle);
	void removeSprite(unsigned int spriteID);
	void removeSprite(std::string spriteID);
	boost::mutex spriteMutex;
	spriteCollision collision;
	void spawn(boost::shared_ptr<genericSprite> spriteToSpawn);
#ifdef SERVER
	EffectManager myEffectManager;
#endif // #ifdef SERVER
private:
    bool active;
	
	
};

extern spriteManager sprite;


#endif // #ifndef spriteManager_hpp
