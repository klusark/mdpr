#include <list>
#include "spriteInterface.hpp"
#include "sprite.hpp"


namespace engine
{
	/**
	 * Initialize The Sprite
	 */
	Sprite::Sprite(const char *name)
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
		for (std::list<engine::spriteInterface *>::iterator it = Interfaces.begin(); it != Interfaces.end(); it++){
			(*it)->update();
		}

	}

	/**
	 * 
	 */
	void Sprite::addInterface(engine::spriteInterface *interfaces)
	{
		Interfaces.push_back(interfaces);

	}

}
