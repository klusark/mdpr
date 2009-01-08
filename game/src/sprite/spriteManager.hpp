#ifndef spriteManager_hpp
#define spriteManager_hpp

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>

#include "genericSprite.hpp"

class spriteManager
{
public:
	spriteManager(bool server = false);
	~spriteManager();
	typedef std::map<int, boost::shared_ptr<genericSprite> > spriteContainer;

	spriteContainer Sprites;
	void registerSprite(boost::shared_ptr<genericSprite> sprite);
	void registerSprite(std::string type, std::string name);
	void update();
	void draw(sf::RenderWindow &App);
	bool isActive();
	void setActive(bool toggle);
private:
    bool active;
	bool server;
};

extern spriteManager sprite;

#endif //spriteManager_hpp
