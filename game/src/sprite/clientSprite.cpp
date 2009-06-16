#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "helpers.hpp"

#include "clientSprite.hpp"

ClientSprite::ClientSprite(const std::string &name) 
	:	sf::Sprite(),
		name(name),
		timesSkiped(0),
		flipped(false),
		currentState(deadState)
{

	SetX(unsigned short(-1));
	SetY(unsigned short(-1));

	/*std::string file;

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
		("image",		boost::program_options::value<std::string>(&image), "")
		("spawnEffect",	boost::program_options::value<std::string>(&spawnEffect), "");

	boost::program_options::variables_map spriteVariableMap;

	boost::program_options::options_description spriteConfigFileOptions;
	spriteConfigFileOptions.add(spriteConfig);
	


	boost::program_options::store(parse_config_file(spriteFileStream, spriteConfigFileOptions), spriteVariableMap);
	notify(spriteVariableMap);
	
	
#ifndef SERVER
	if (image.length() != 0){
		//load image hackish way to check if in a thread
		if (Image.GetHeight() == 0 ){
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
		unsigned int animationName = stringToCRC(*iter);
		Animations[animationName] = newAnimation;
			
	}*/
}

ClientSprite::~ClientSprite()
{
}

void ClientSprite::update()
{
	//SetSubRect(currentAnimation->update());
	FlipX(flipped);
}

void ClientSprite::draw(sf::RenderWindow &App)
{
	App.Draw(*this);
}
