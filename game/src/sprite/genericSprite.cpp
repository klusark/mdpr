#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "genericSprite.hpp"

genericSprite::genericSprite(const std::string &resourceLocation) : CL_Sprite()
{
	last_time = 0;
	x = 0.5f;
	y = 0.5f;
	xVelocity = 0;
	yVelocity = 0;
	xAccel = 0;
	yAccel = 0;
	resources = new CL_ResourceManager(resourceLocation);
}

genericSprite::~genericSprite()
{
	delete resources;
}

void genericSprite::update()
{
	CL_Sprite::update();

	float new_time = static_cast<float>(CL_System::get_time());
	if(last_time == 0)
		last_time = new_time;

	float delta_time = (new_time - last_time) / 1000.0f;
	last_time = new_time;

	x+=xVelocity*delta_time+(0.5)*xAccel*pow(delta_time,2);
	y+=yVelocity*delta_time+(0.5)*yAccel*pow(delta_time,2);

}

float genericSprite::round(float number)
{
	float temp = number-floor(number);
	if (temp < 0.5){
		return floor(number);
	}else{
		return ceil(number);
	}
}

float genericSprite::getX()
{

	if (xVelocity == 0){
		return round(x);
	}else{
		return x;
	}
}

float genericSprite::getY()
{
	if (yVelocity == 0){
		return round(y);
	}else{
		return y;
	}
}