#include <SDL.h>
#include <time.h>

#include "main.hpp"
#include "player.hpp"
#include "video.hpp"
#include "bubble.hpp"
#include "level.hpp"
#include "game.hpp"

namespace game
{
	//players
	player player1;
	player player2;
	
	//bubbles
	bubble bubble[3];

	Uint32 LastTime = SDL_GetTicks();
	unsigned int ShownFrames = 0;

	//game::init
	//Gets the game setup
	//Parameters: None
	//Return: None
	void init()
	{
		srand((unsigned)time(NULL));
		//init the level
		level::init();
		
		//init the players
		player1.init(1);
		player2.init(2);

		//init the bubbles
		for (int i = 0; i<3; i++){
			bubble[i].init();
		}
	}

	//game::mainLoop
	//The main loop for ingame
	//Parameters: None
	//Return: None
	void mainLoop()
	{
		
		//calc fps
		ShownFrames++;
		if((SDL_GetTicks() - LastTime) >= 1000)
		{
			printf("%li\n", ShownFrames);
	 
			ShownFrames = 0;
			LastTime = SDL_GetTicks();
		}

		//draw the level
		level::update();

		//update the bubbles
		for (int i = 0; i<3; i++){
			bubble[i].update();
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
