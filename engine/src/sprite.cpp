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
	}

	/**
	 * 
	 */
	//void Sprite::implement

}
