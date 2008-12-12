#ifndef genericSprite_hpp
#define genericSprite_hpp

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class genericSprite : public CL_Sprite
{
public:
	genericSprite(const std::string &resourceLocation);
	~genericSprite();
	float getX();
	float getY();
	void update();
	float round(float number);
protected:
	CL_ResourceManager *resources;
	float x,			y;
	float xAccel,		yAccel;
	float xVelocity,	yVelocity;
	float last_time;

};

#endif
