#include <boost/shared_ptr.hpp>

#include <string>

#include <SFML/Graphics/Sprite.hpp>

#include "genericSprite.hpp"

genericSprite::genericSprite(const std::string &name) : sf::Sprite(), name(name)
{
	//last_time = 0;
	x = 0;
	y = 0;
	xVelocity = 1;
	yVelocity = 0;
	xAccel = 5;
	yAccel = 0;
	SetX(0);
	SetY(0);

	//boost::shared_ptr<CL_ResourceManager> tmpResources(new CL_ResourceManager(resourceLocation));
	//resources = tmpResources;


}

genericSprite::~genericSprite()
{
}

void genericSprite::update()
{
	//if (!server){
	//	CL_Sprite::update();
	//}

/*	float new_time = static_cast<float>(CL_System::get_time());
	if(last_time == 0)
		last_time = new_time;

	float delta_time = (new_time - last_time)/1000.0f;
	last_time = new_time;

	x+=static_cast<float>(xVelocity*delta_time+(0.5)*xAccel*pow(delta_time,2));
	y+=static_cast<float>(yVelocity*delta_time+(0.5)*yAccel*pow(delta_time,2));
	xVelocity+=xAccel*delta_time;
	yVelocity+=yAccel*delta_time;
*/
}

void genericSprite::changeAnimation(std::string name)
{
/*	animationContainer iter;
	if (Animations.find(name) != Animations.end()){
		//set_image_data(*Animations[name]);
	}else{
		std::cout<<"asdfsadfsf";
	}
*/
}

void genericSprite::loadAnimation(std::string name)
{
	//boost::shared_ptr<CL_Sprite> tmpAnimation(new CL_Sprite(name, resources.get()));
//	Animations[name] = tmpAnimation;

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

float genericSprite::getXVelocity()
{
	return xVelocity;
}

float genericSprite::getYVelocity()
{
	return yVelocity;
}

void genericSprite::setXVelocity(float xVelocity)
{
	this->xVelocity = xVelocity;
}

void genericSprite::setYVelocity(float yVelocity)
{
	this->yVelocity = yVelocity;
}
