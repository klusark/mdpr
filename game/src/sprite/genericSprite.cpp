#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "genericSprite.hpp"

genericSprite::genericSprite(const std::string &resourceLocation) : CL_Sprite()
{
	last_time = 0;
	x = 0;
	y = 0;
	xVelocity = 1;
	yVelocity = 1;
	xAccel = 5;
	yAccel = 0;
	resources = new CL_ResourceManager(resourceLocation);
}

genericSprite::~genericSprite()
{
	delete resources;
	for(animationContainer::iterator it = Sprites.begin(); it != Sprites.end(); ++it){
		delete it->second;
	}
}

void genericSprite::update()
{
	CL_Sprite::update();

	float new_time = static_cast<float>(CL_System::get_time());
	if(last_time == 0)
		last_time = new_time;

	float delta_time = (new_time - last_time);
	last_time = new_time;

	x+=static_cast<float>((xVelocity/1000)*delta_time+(0.5)*(xAccel/1000)*pow(delta_time,2));
	y+=static_cast<float>((yVelocity/1000)*delta_time+(0.5)*(yAccel/1000)*pow(delta_time,2));
	xVelocity+=(xAccel/1000)*delta_time;
	yVelocity+=(yAccel/1000)*delta_time;

}

void genericSprite::changeAnimation(std::string name)
{
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