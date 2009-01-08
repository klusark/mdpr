#ifndef genericSprite_hpp
#define genericSprite_hpp

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Clock.hpp>
#include <map>

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

	void update();
	float round(float number);
	void changeAnimation(std::string name);
	void loadAnimation(std::string name);

	std::string name;
protected:
	bool server;
	float xAccel,		yAccel;
	float xVelocity,	yVelocity;
	sf::Clock Clock;
	sf::Image &Image;
	
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

	};
	typedef std::map<std::string, boost::shared_ptr<Animation> > animationContainer;
	animationContainer Animations;
	boost::shared_ptr<Animation> currentAnimation;

};

#endif
