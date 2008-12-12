#ifndef genericSprite_hpp
#define genericSprite_hpp

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
	void update();
	float round(float number);
	void changeAnimation(std::string name);
	void loadAnimation(std::string name);
	const std::string name;
protected:
	CL_ResourceManager *resources;
	float x,			y;
	float xAccel,		yAccel;
	float xVelocity,	yVelocity;
	float last_time;
	typedef std::map<std::string, CL_Sprite *> animationContainer;
	animationContainer Animations;

};

#endif
