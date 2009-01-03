#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "genericSprite.hpp"

genericSprite::genericSprite(const std::string &name, sf::Image &tempImage) 
	:	sf::Sprite(),
		name(name),
		Image(tempImage)
{
	//last_time = 0;
	//Image = new sf::Image();
	//getImage(*Image);
	

	xVelocity = 1;
	yVelocity = 0;
	xAccel = 5;
	yAccel = 0;
	SetX(0);
	SetY(0);
	
	std::vector<std::string> animations;
	std::string image;
	boost::program_options::options_description spriteConfig("Configuration");
	spriteConfig.add_options()
		("animation",	boost::program_options::value<std::vector<std::string> >(&animations), "")
		("image",		boost::program_options::value<std::string>(&image), "");

	boost::program_options::variables_map spriteVariableMap;

	boost::program_options::options_description spriteConfigFileOptions;
	spriteConfigFileOptions.add(spriteConfig);
	

	std::ifstream spriteFileStream("data/mdpr/sprites/player/player.sprite");

	boost::program_options::store(parse_config_file(spriteFileStream, spriteConfigFileOptions), spriteVariableMap);
	notify(spriteVariableMap);
	
	
	
	//load image hackish way to check if in a thread
	if (Image.GetHeight() == 0 && !boost::this_thread::interruption_enabled()){
		Image.LoadFromFile("data/mdpr/sprites/player/player.png");
		Image.SetSmooth(false);
	}
	SetImage(Image);

	std::vector< std::string >::iterator iter;
	for (iter = animations.begin(); iter < animations.end(); ++iter){
		//Animation test;

		//int delay, frames, startx, starty, width, height;
		boost::program_options::options_description animationConfig("Configuration");
		boost::shared_ptr<Animation> newAnimation(new Animation);

		animationConfig.add_options()
			("delay",	boost::program_options::value< int >(&newAnimation->delay),	"")
			("frames",	boost::program_options::value< int >(&newAnimation->frames),	"")
			("startx",	boost::program_options::value< int >(&newAnimation->startx),	"")
			("starty",	boost::program_options::value< int >(&newAnimation->starty),	"")
			("width",	boost::program_options::value< int >(&newAnimation->width),	"")
			("height",	boost::program_options::value< int >(&newAnimation->height),	"");

		boost::program_options::variables_map animationVariableMap;

		boost::program_options::options_description animationConfigFileOptions;
		animationConfigFileOptions.add(animationConfig);
		
		std::string animationFileName;
		animationFileName = "data/mdpr/sprites/player/";
		animationFileName += *iter;
		animationFileName += ".animation";
		//std::cout << *iter;

		std::ifstream animationFileStream(animationFileName.c_str());

		boost::program_options::store(parse_config_file(animationFileStream, animationConfigFileOptions), animationVariableMap);
		notify(animationVariableMap);
		Animations[*iter] = newAnimation;
			
	}
	currentAnimation = Animations["run"];



	//boost::shared_ptr<CL_ResourceManager> tmpResources(new CL_ResourceManager(resourceLocation));
	//resources = tmpResources;


}

genericSprite::~genericSprite()
{
}

void genericSprite::update()
{
	SetSubRect(currentAnimation->update());
	//SetSubRect(sf::IntRect(0, 0, 24, 24));
	//if (!server){
	//	CL_Sprite::update();
	//}

	//float new_time = static_cast<float>(CL_System::get_time());

	
	float delta_time = Clock.GetElapsedTime();
	Clock.Reset();

	Move(sf::Vector2<float>::Vector2(static_cast<float>(xVelocity*delta_time+(0.5)*xAccel*pow(delta_time,2)), static_cast<float>(yVelocity*delta_time+(0.5)*yAccel*pow(delta_time,2))));
	xVelocity+=xAccel*delta_time;
	yVelocity+=yAccel*delta_time;

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

sf::IntRect genericSprite::Animation::update()
{
	
	sf::IntRect test(currentFrame*width+startx, starty, width+currentFrame*width, starty+height);

	updateTime += Clock.GetElapsedTime()*1000;
	Clock.Reset();
	while(updateTime > delay){
		updateTime -= delay;
		currentFrame = playBackward ? currentFrame -1 : currentFrame + 1;
		
		if(currentFrame >= frames || currentFrame < 0)
		{
			currentFrame = playBackward ? frames - 1 : 0;
		}
	}




	return test;
	
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
