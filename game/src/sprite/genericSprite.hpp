#ifndef genericSprite_hpp
#define genericSprite_hpp

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Clock.hpp>
#include <map>
#include "../network/packets.hpp"

class genericSprite : public sf::Sprite
{
public:
	genericSprite(const std::string &name, std::string spriteType, sf::Image &Image);
	~genericSprite();

	float getXAccel();
	float getYAccel();
	void setXAccel(float xAccel);
	void setYAccel(float yAccel);

	float getXVelocity();
	float getYVelocity();
	void setXVelocity(float xVelocity);
	void setYVelocity(float yVelocity);

	virtual void update();
	virtual void draw(sf::RenderWindow &App);

	float round(float number);
	void changeAnimation(unsigned int name);

	std::string name;

	spriteTypes spriteType;

	class Animation
	{
	public:
		Animation()
		{
			currentFrame = 0;
			updateTime = 0;
			playBackward = false;
		}
		sf::Clock Clock;
		float updateTime;
		int delay, frames, startx, starty, width, height, currentFrame;
		bool playBackward;
		sf::IntRect update();
		sf::IntRect collisionRect;

	};

	boost::shared_ptr<Animation> currentAnimation;
	bool onGround;
protected:
	float xAccel,		yAccel;
	float xVelocity,	yVelocity;
	sf::Clock Clock;
	sf::Image &Image;
	

	typedef std::map<unsigned int, boost::shared_ptr<Animation> > animationContainer;
	animationContainer Animations;
	

};

#endif // ifndef genericSprite_hpp
