#include "engineLib.hpp"
#include "spriteCollision.hpp"
#include <iostream>
namespace engine
{

	/**
	 * Initialize The Collision System for the sprite
	 */
	Collision::Collision()
	{

	}

	/**
	 * Destroys The Collision System for the sprite
	 */
	Collision::~Collision()
	{

	}

	/**
	 * Updates The Collision System for the sprite
	 * Takes care of checking for collisions to other sprites
	 */
	void Collision::update()
	{

	}

	void Collision::setCollisionType(std::string name)
	{
		collisionType = name;
	}

	void Collision::colidesWith(std::string name, unsigned int direction)
	{
		collisionInfo temp;
		temp.name = name;
		temp.direction = direction;
		collisions.push_back(temp);
	}

	std::string Collision::getName()
	{
		return "collision";
	}
}
