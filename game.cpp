#include "game.hpp"

namespace game
{
	//define players
	player player1;
	player player2;
	
	//bubbles
	bubble bubble1;
	
	unsigned int ShownFrames = 0;

	//set frame max to 60fps
	Uint32 wait = (Uint32)(1000 / 60);

	Uint32 bticks, cticks;
	Uint32 LastTime = SDL_GetTicks();

	//game::init
	//Gets the game setup
	//Parameters: None
	//Return: None
	void init()
	{
		//init the level
		level::init();

		//init the players
		player1.init();
		player2.init();

		//init the bubble
		bubble1.init();
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
		bubble1.update();
		
		//update player 1
		player1.update();

		//update player 2
		player2.update();
		
		video::switchBuf();

		//clear the screen
		SDL_FillRect(video::screen, &video::screen->clip_rect, SDL_MapRGB(video::screen->format, 0, 0, 0)); 

		//limit the framerate
		cticks = SDL_GetTicks();
		if ((cticks - bticks) < wait){
			//framerate exceeded limit....so we wait the difference
			SDL_Delay(wait - (cticks - bticks));
		}
		bticks = SDL_GetTicks();

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
