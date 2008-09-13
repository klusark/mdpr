#include <SDL.h>
#include <time.h>

#include "main.hpp"
#include "player.hpp"
#include "video.hpp"
#include "bubble.hpp"
#include "level.hpp"
#include "game.hpp"

/*
* the name space all the game stuff
* TODO change this to a class
*/
namespace game
{
	//players
	player player1;
	player player2;
	
	//bubbles
	bubble bubbles[3];

	Uint32 lastTime = SDL_GetTicks();
	unsigned int shownFrames = 0;

	/*
	* gets the game setup
	*/
	void init()
	{
		//seed the prng with the current time
		srand((unsigned)time(NULL));

		//init the level
		level::init();
		
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
	void mainLoop()
	{
		
		//calc fps
		shownFrames++;
		if((SDL_GetTicks() - lastTime) >= 1000)
		{
			printf("%li\n", shownFrames);
	 
			shownFrames = 0;
			lastTime = SDL_GetTicks();
		}

		//draw the level
		level::update();

		//update the bubbles
		for (int i = 0; i<3; i++){
			bubbles[i].update();
		}

		//update player 1
		player1.update();

		//update player 2
		player2.update();

		//switch the buffer
		video::switchBuf();

		//clear the screen
		SDL_FillRect(video::screen, &video::screen->clip_rect, SDL_MapRGB(video::screen->format, 0, 0, 0)); 

		//limit the framerate
		//video::limitFPS(60);

		return;
	}

	//from lazyfoo TODO write my own
	bool checkCollision(SDL_Rect rectA, SDL_Rect rectB)
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

}
