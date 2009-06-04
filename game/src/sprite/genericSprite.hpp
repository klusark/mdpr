#ifndef genericSprite_hpp
#define genericSprite_hpp

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Clock.hpp>
#include <map>
#include "../enumerations.hpp"

#include "animation.hpp"

class genericPowerUp;

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

	void changeAnimation(unsigned int name);
	void changeAnimation(std::string name);

	void kill();

	virtual void die();

	std::string name;

	boost::shared_ptr<genericPowerUp> currentPowerup;
	bool hasPowerUp;
	bool onGround;
	bool inputDisabled;
	bool nonNetworked;
	bool keyLock;
	bool animationLock;
	bool noAnimation;

	std::string lastAnimationName;

	spriteTypes spriteType;

	boost::shared_ptr<Animation> currentAnimation;
	
	float lastX, lastY;
	int timesSkiped;
	bool flipped;
protected:
	sf::Image &Image;
	float xAccel,		yAccel;
	float xVelocity,	yVelocity;
	
	sf::Clock Clock;

	typedef std::map<unsigned int, boost::shared_ptr<Animation> > animationContainer;
	animationContainer Animations;
};

#endif // ifndef genericSprite_hpp
