#ifndef player_hpp
#define player_hpp

#include "genericSprite.hpp"
#include "../enumerations.hpp"
#include <SFML/Graphics/Image.hpp>

class Player : public genericSprite
{
public:
	Player(const std::string &name);
	~Player();
	void update();
	void crouchingFinish();
	static sf::Image Image;
	typedef std::map<keys, bool> keysContainter;
	keysContainter keyMap;
	bool rolling, running, crouching, idle;
	
};

#endif // ifndef player_hpp
