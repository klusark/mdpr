#ifndef deathArea_hpp
#define deathArea_hpp

#include <SFML/Graphics/Image.hpp>

#include "genericSprite.hpp"


class selectionArea : public genericSprite
{
public:
	selectionArea(const std::string &name, sf::IntRect rect);
	~selectionArea();
	static sf::Image Image;
	sf::IntRect collisionRect;
	bool collisionChecked;
	void update();
	void draw();
	
};

#endif // ifndef deathArea_hpp
