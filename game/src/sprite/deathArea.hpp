#ifndef deathArea_hpp
#define deathArea_hpp

#include <SFML/Graphics/Image.hpp>

#include "genericSprite.hpp"


class DeathArea : public genericSprite
{
public:
	DeathArea(const std::string &name, sf::IntRect rect);
	~DeathArea();
	static sf::Image Image;
	sf::IntRect collisionRect;
	bool collisionChecked;
	void update();
	void draw();
	
};

#endif // ifndef deathArea_hpp
