#include "SpriteManager.hpp"

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
}

void SpriteManager::tick()
{
	if (player1 != 0)
		player1->update();

	if (player2 != 0)
		player2->update();
}
