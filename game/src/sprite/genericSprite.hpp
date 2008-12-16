#ifndef genericSprite_hpp
#define genericSprite_hpp

#include <boost/shared_ptr.hpp>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <map>

class genericSprite : public CL_Sprite
{
public:
	genericSprite(const std::string &resourceLocation, const std::string &name);
	~genericSprite();

	float getX();
	float getY();
	void setX(float X);
	void setY(float Y);

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
	boost::shared_ptr<CL_ResourceManager> resources;
	float x,			y;
	float xAccel,		yAccel;
	float xVelocity,	yVelocity;
	float last_time;
	typedef std::map<std::string, boost::shared_ptr<CL_Sprite> > animationContainer;
	animationContainer Animations;

};

#endif
