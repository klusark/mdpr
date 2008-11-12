#include "engineLib.hpp"
#include <map>
#include "spriteInterface.hpp"
#include "sprite.hpp"


namespace engine
{
	/**
	 * Initialize The Sprite
	 */
	Sprite::Sprite(std::string name)
	{
		Sprite::name = name;
		//makeAnimation("run", 4, 100, "run0", "run1", "run2", "run3");
		//changeAnimation("run");
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

}
