#ifndef genericSprite_hpp
#define genericSprite_hpp

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <map>

class genericSprite : public sf::Sprite
{
public:
	genericSprite(const std::string &name);
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
	//boost::shared_ptr<CL_ResourceManager> resources;
	float x,			y;
	float xAccel,		yAccel;
	float xVelocity,	yVelocity;
	sf::Clock Clock;
	//typedef std::map<std::string, boost::shared_ptr<CL_Sprite> > animationContainer;
	//animationContainer Animations;

};

#endif
