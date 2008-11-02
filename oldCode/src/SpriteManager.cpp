#include "Player.hpp"
#include "Bubble.hpp"
#include "Effect.hpp"
#include "SpriteManager.hpp"

/**
 * consturcts the spritemanager
 */
SpriteManager::SpriteManager(SDL_Surface *screen)
{
	this->screen = screen;
}

SpriteManager::~SpriteManager()
{
}

void SpriteManager::tick()
{
	if (player1 != 0){
		player1->update();
	}

	if (player2 != 0){
		player2->update();
	}

	for (short i = 0; i<3; ++i){
		if (bubbles[i] != 0){
			bubbles[i]->update();
		}
	}

	for (short i = 0; i<2; ++i){
		if (effects[i] != 0){
			if (effects[i]->isInUse()){
				effects[i]->update();
			}
		}
	}

	checkCollions();
}

void SpriteManager::checkCollions()
{

}
