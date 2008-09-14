#include <SDL.h>
#include <time.h>

#include "main.hpp"
#include "player.hpp"
#include "video.hpp"
#include "bubble.hpp"
#include "level.hpp"
#include "game.hpp"

/*
* gets the game setup
*/
void Game::init()
{
	//seed the prng with the current time
	srand((unsigned)time(NULL));

	//init the level
	level.init();
	
	//init the players
	player1.init(1);
	player2.init(2);

	//init the bubbles
	for (int i = 0; i<3; i++){
		bubbles[i].init();
	}
}

/*
* the main loop for ingame
*/
void Game::mainLoop()
{
	
	//calc fps
	shownFrames++;
	if((SDL_GetTicks() - lastTime) >= 1000)
	{
		printf("%u\n", shownFrames);
 
		shownFrames = 0;
		lastTime = SDL_GetTicks();
	}

	//update the bubbles
	for (int i = 0; i<3; i++){
		bubbles[i].update();
	}

	//update player 1
	player1.update();

	//update player 2
	player2.update();

	//draw the level
	level.update();

	//blit the images in the queue
	video::blitImageQueue();

	//switch the buffer
	video::switchBuf();

	//limit the framerate
	video::limitFPS(60);

	return;
}

//from lazyfoo TODO write my own
bool Game::checkCollision(SDL_Rect rectA, SDL_Rect rectB)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = rectA.x;
	rightA = rectA.x + rectA.w;
	topA = rectA.y;
	bottomA = rectA.y + rectA.h;
        
	//Calculate the sides of rect B
	leftB = rectB.x;
	rightB = rectB.x + rectB.w;
	topB = rectB.y;
	bottomB = rectB.y + rectB.h;
	//If any of the sides from A are outside of B
	if( bottomA <= topB )
	{
		return false;
	}
    
	if( topA >= bottomB )
	{
		return false;
	}
    
	if( rightA <= leftB )
	{
		return false;
	}
    
	if( leftA >= rightB )
	{
		return false;
	}
    
	//If none of the sides from A are outside B
	return true;
}

