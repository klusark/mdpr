#ifndef spriteManager_hpp
#define spriteManager_hpp

#include <map>
#include <string>
#include "genericSprite.hpp"
#include <boost/shared_ptr.hpp>

class spriteManager
{
public:
	spriteManager(bool server = false);
	~spriteManager();
	typedef std::map<std::string, boost::shared_ptr<genericSprite> > spriteContainer;

	spriteContainer Sprites;
	void registerSprite(boost::shared_ptr<genericSprite> sprite);
	void registerSprite(std::string type, std::string name);
	void update();
	void draw();
	bool isActive();
	void setActive(bool toggle);
private:
    bool active;
	bool server;
};

extern boost::shared_ptr<spriteManager> sprite;

#endif
