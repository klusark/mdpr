#ifndef player_hpp
#define player_hpp

#include "genericSprite.hpp"
#include <SFML/Graphics/Image.hpp>

class Player : public genericSprite
{
public:
	Player(const std::string &name);
	~Player();
	static sf::Image Image;
	
};

#endif
