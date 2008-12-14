#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "genericSprite.hpp"

genericSprite::genericSprite(const std::string &resourceLocation, const std::string &name) : CL_Sprite(), name(name)
{
	last_time = 0;
	x = 0;
	y = 0;
	xVelocity = 1;
	yVelocity = 0;
	xAccel = 5;
	yAccel = 0;
	resources = new CL_ResourceManager(resourceLocation);
}

genericSprite::~genericSprite()
{
	delete resources;
	for(animationContainer::iterator it = Animations.begin(); it != Animations.end(); ++it){
		delete it->second;
	}
}

void genericSprite::update()
{
	CL_Sprite::update();

	float new_time = static_cast<float>(CL_System::get_time());
	if(last_time == 0)
		last_time = new_time;

	float delta_time = (new_time - last_time)/1000.0f;
	last_time = new_time;

	x+=static_cast<float>(xVelocity*delta_time+(0.5)*xAccel*pow(delta_time,2));
	y+=static_cast<float>(yVelocity*delta_time+(0.5)*yAccel*pow(delta_time,2));
	xVelocity+=xAccel*delta_time;
	yVelocity+=yAccel*delta_time;

}

void genericSprite::changeAnimation(std::string name)
{
	animationContainer iter;
	if (Animations.find(name) != Animations.end()){
		set_image_data(*Animations[name]);
	}else{
		std::cout<<"asdfsadfsf";
	}
}

void genericSprite::loadAnimation(std::string name)
{
	Animations[name] = new CL_Sprite(name, resources);

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
	if (x>320)
		x=0;

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

void genericSprite::setX(float X)
{
	this->x = X;
}

void genericSprite::setY(float Y)
{
	this->y = Y;
}

float genericSprite::getXAccel()
{
	return xAccel;
}

float genericSprite::getYAccel()
{
	return yAccel;
}

void genericSprite::setXAccel(float xAccel)
{
	this->xAccel = xAccel;
}

void genericSprite::setYAccel(float yAccel)
{
	this->yAccel = yAccel;
}