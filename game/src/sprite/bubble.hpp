#ifndef bubble_hpp
#define bubble_hpp

#include "genericSprite.hpp"
#include <SFML/Graphics/Image.hpp>
#include "powerup.hpp"

class Bubble : public genericSprite
{
public:
	Bubble(const std::string &name);
	~Bubble();
	static sf::Image Image;
	void update();
	void draw(sf::RenderWindow &App);
	PowerUp powerup;
	
};

#endif
