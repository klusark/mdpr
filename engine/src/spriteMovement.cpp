#include "engineLib.hpp"
#include "spriteMovement.hpp"
namespace engine
{

	/**
	 * Initialize The Movement System for the sprite
	 */
	Movement::Movement()
	{
		

	}

	/**
	 * Destroys The Movement System for the sprite
	 */
	Movement::~Movement()
	{

	}

	/**
	 * Updates The Movement System for the sprite
	 * Takes care of moving the sprite
	 */
	void Movement::update()
	{

		//unsigned int xTime = SDL_GetTicks()-xLastTime;
		//x+=(xVelocity*xTime)+0.5*xAcceleration*xTime*xTime;
	}

	std::string Movement::getName()
	{
		return "movement";
	}
}
