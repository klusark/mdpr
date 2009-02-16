#ifndef animation_hpp
#define animation_hpp

#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\Rect.hpp>

class Animation
{
public:
	Animation(std::string name);
	std::string name;
	sf::Clock Clock;
	float updateTime;
	int delay, frames, startx, starty, width, height, currentFrame;
	bool playBackward, reverseonfinish;
	sf::IntRect update();
	sf::IntRect collisionRect;

};

#endif // ifndef animation_hpp
