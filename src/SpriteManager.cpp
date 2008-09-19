#include "Player.hpp"
#include "Bubble.hpp"
#include "Effect.hpp"
#include "SpriteManager.hpp"

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
			//bubbles[i]->update();
		}
	}
	//update any current effects
	//for (std::vector<Effect*>::iterator Iter = effects.begin(); Iter != effects.end(); ++Iter){
		//(*Iter)->update();
	//}


	checkCollions();
}

void SpriteManager::checkCollions()
{

}
