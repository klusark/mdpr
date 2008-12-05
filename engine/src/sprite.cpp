#include "engineLib.hpp"
#include "spriteInterface.hpp"
#include "sprite.hpp"
#include "spriteAnimation.hpp"
#include <map>
#include <iostream>
#include <fstream>

namespace engine
{
	/**
	 * Initialize The Sprite
	 */
	Sprite::Sprite(std::string name)
	{
		Sprite::name = name;
	}

	Sprite::Sprite(std::string name, std::ifstream &spriteFile)
	{
		Sprite::name = name;
		std::string line;
		while (!spriteFile.eof()){
			spriteFile>>line;
			if (line.compare("name") == 0){
			}else if(line.compare("animaiton") == 0){
				if (!isInterfaceAdded("animation")){
					engine::spriteInterface *animation = new engine::Animation;
					addInterface(animation);
				}
				

				std::string name;
				spriteFile>>name;

				std::string numFrames;
				spriteFile>>numFrames;
				unsigned short numFramesI = static_cast<unsigned short>(atoi(numFrames.c_str()));

				std::string delay;
				spriteFile>>delay;
				unsigned short delayI = static_cast<unsigned short>(atoi(delay.c_str()));

				std::string frames;
				spriteFile>>frames;

				dynamic_cast<engine::Animation*>(Interfaces["animation"])->makeAnimation(name, numFramesI, delayI, frames);


			}else{
				std::cout<<"Syntax error in sprite"<<std::endl;
				throw 1;
				return;
			}
		}
	}

	/**
	 * Destroys The Sprite
	 */
	Sprite::~Sprite()
	{
	}

	/**
	 * Updates the sprite doing any drawing needed.
	 */
	void Sprite::update()
	{
		for (std::map<std::string, engine::spriteInterface *>::iterator it = Interfaces.begin(); it != Interfaces.end(); it++){
			it->second->update();
		}

	}

	/**
	 * adds a interface to the current spire
	 * @param interfaces the interface
	 */
	void Sprite::addInterface(engine::spriteInterface *interfaces)
	{
		Interfaces[interfaces->getName()] = interfaces;

	}

	bool Sprite::isInterfaceAdded(std::string interfaceName)
	{
		std::map<std::string, engine::spriteInterface *>::iterator iterator;
		iterator = Interfaces.find(interfaceName);
		if (iterator == Interfaces.end()){
			return false;
		}
		return true;
	}

}
