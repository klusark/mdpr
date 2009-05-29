#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#ifndef SERVER
#include <boost/thread.hpp>
#endif
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "../helpers.hpp"

#include "../powerup/genericPowerUp.hpp"
#include "genericSprite.hpp"

genericSprite::genericSprite(const std::string &name, std::string spriteType, sf::Image &tempImage) 
	:	sf::Sprite(),
		name(name),
		Image(tempImage),
		xVelocity(0),
		yVelocity(0),
		xAccel(0),
		yAccel(0),
		lastX(0),
		lastY(0),
		timesSkiped(0),
		hasPowerUp(false),
		flipped(false),
		nonNetworked(false),
		animationLock(false),
		keyLock(false),
		noAnimation(false)
{

	SetX(0);
	SetY(0);

	std::string file;

	file = "data/mdpr/sprites/";
	file += spriteType;
	file += "/";
	file += spriteType;
	file += ".sprite";

	std::ifstream spriteFileStream(file.c_str());
	if (!spriteFileStream.is_open()){
		noAnimation = true;
		return;
	}

	std::vector<std::string> animations;
	std::string image;
	boost::program_options::options_description spriteConfig("Configuration");
	spriteConfig.add_options()
		("animation",	boost::program_options::value<std::vector<std::string> >(&animations), "")
		("image",		boost::program_options::value<std::string>(&image), "");

	boost::program_options::variables_map spriteVariableMap;

	boost::program_options::options_description spriteConfigFileOptions;
	spriteConfigFileOptions.add(spriteConfig);
	


	boost::program_options::store(parse_config_file(spriteFileStream, spriteConfigFileOptions), spriteVariableMap);
	notify(spriteVariableMap);
	
	
#ifndef SERVER
	if (image.length() != 0){
		//load image hackish way to check if in a thread
		if (Image.GetHeight() == 0 /*&& !boost::this_thread::interruption_enabled()*/){
			std::string imageFile;
			imageFile = "data/mdpr/sprites/";
			imageFile += spriteType;
			imageFile += "/";
			imageFile += image;
			Image.LoadFromFile(imageFile);
			Image.SetSmooth(false);
		}
		SetImage(Image);
	}
#endif // #ifndef SERVER
	std::vector< std::string >::iterator iter;
	for (iter = animations.begin(); iter < animations.end(); ++iter){

		boost::program_options::options_description animationConfig("Configuration");
		boost::shared_ptr<Animation> newAnimation(new Animation(*iter));
		
		animationConfig.add_options()
			("delay",	boost::program_options::value<int>(&newAnimation->AnimationInfo.delay),		"")
			("frames",	boost::program_options::value<int>(&newAnimation->AnimationInfo.frames),	"")
			("startx",	boost::program_options::value<int>(&newAnimation->AnimationInfo.startx),	"")
			("starty",	boost::program_options::value<int>(&newAnimation->AnimationInfo.starty),	"")
			("width",	boost::program_options::value<int>(&newAnimation->AnimationInfo.width),		"")
			("height",	boost::program_options::value<int>(&newAnimation->AnimationInfo.height),	"")
			("padding",	boost::program_options::value<int>(&newAnimation->AnimationInfo.padding),	"")
			("reverseOnFinish",			boost::program_options::value<bool>(&newAnimation->AnimationInfo.reverseOnFinish),		"")
			("pauseOnFinish",			boost::program_options::value<bool>(&newAnimation->AnimationInfo.pauseOnFinish),		"")

			("collision.rect.top",		boost::program_options::value<int >(&newAnimation->AnimationInfo.collisionRect.Top),	"")
			("collision.rect.bottom",	boost::program_options::value<int >(&newAnimation->AnimationInfo.collisionRect.Bottom),	"")
			("collision.rect.right",	boost::program_options::value<int >(&newAnimation->AnimationInfo.collisionRect.Right),	"")
			("collision.rect.left",		boost::program_options::value<int >(&newAnimation->AnimationInfo.collisionRect.Left),	"");

		boost::program_options::variables_map animationVariableMap;

		boost::program_options::options_description animationConfigFileOptions;
		animationConfigFileOptions.add(animationConfig);
		
		std::string animationFileName;
		animationFileName = "data/mdpr/sprites/";
		animationFileName += spriteType;
		animationFileName += "/";
		animationFileName += *iter;
		animationFileName += ".animation";

		std::ifstream animationFileStream(animationFileName.c_str());

		boost::program_options::store(parse_config_file(animationFileStream, animationConfigFileOptions), animationVariableMap);
		notify(animationVariableMap);
		unsigned int test = stringToCRC(*iter);
		Animations[test] = newAnimation;
			
	}
}

genericSprite::~genericSprite()
{
}

void genericSprite::update()
{
	if(!noAnimation){
#ifndef SERVER
		SetSubRect(currentAnimation->update());
		FlipX(flipped);
#else 
		currentAnimation->update();
#endif
	}
	float deltaTime = Clock.GetElapsedTime();
	Clock.Reset();

	Move(sf::Vector2<float>::Vector2(static_cast<float>(xVelocity*deltaTime+(0.5)*xAccel*pow(deltaTime,2)), static_cast<float>(yVelocity*deltaTime+(0.5)*yAccel*pow(deltaTime,2))));
	xVelocity+=xAccel*deltaTime;
	yVelocity+=yAccel*deltaTime;
	if (hasPowerUp){
		currentPowerup->update();
	}

}

void genericSprite::draw(sf::RenderWindow &App)
{
	App.Draw(*this);
}

void genericSprite::changeAnimation(unsigned int name)
{
	if (!animationLock){
		if (Animations.find(name) != Animations.end()){
			currentAnimation = Animations[name];
			currentAnimation->Clock.Reset();
		}else{
			std::cout << "Error Cannot find Animation: " << name << std::endl;
		}
	}
}

void genericSprite::changeAnimation(std::string name)
{
	changeAnimation(stringToCRC(name));
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
