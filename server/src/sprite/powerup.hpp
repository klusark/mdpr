#ifndef powerup_hpp
#define powerup_hpp

#include "genericSprite.hpp"
#include <SFML/Graphics/Image.hpp>

class PowerUp : public genericSprite
{
public:
	PowerUp(const std::string &name);
	~PowerUp();
	static sf::Image Image;
};

#endif // ifndef powerup_hpp
