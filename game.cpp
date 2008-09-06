#include "game.hpp"

namespace game
{
	SDL_Rect platforms[16];
	player Player1;
	Uint32 LastTime = SDL_GetTicks();
	unsigned int ShownFrames = 0;
	//set frame max to 60fps
	Uint32 wait = (Uint32)(1000 / 60);
	Uint32 bticks, cticks;

	//game::init
	//Gets the game setup
	//Parameters: None
	//Return: None
	void init()
	{	
		//bottom left
		game::platforms[0].x = 25;
		game::platforms[0].y = 168;

		game::platforms[1].x = 41;
		game::platforms[1].y = 168;

		game::platforms[2].x = 57;
		game::platforms[2].y = 168;

		game::platforms[3].x = 73;
		game::platforms[3].y = 168;

		//bottom right
		game::platforms[4].x = 233;
		game::platforms[4].y = 168;

		game::platforms[5].x = 249;
		game::platforms[5].y = 168;

		game::platforms[6].x = 265;
		game::platforms[6].y = 168;

		game::platforms[7].x = 281;
		game::platforms[7].y = 168;

		//top left
		game::platforms[8].x = 49;
		game::platforms[8].y = 40;

		game::platforms[9].x = 65;
		game::platforms[9].y = 40;

		game::platforms[10].x = 81;
		game::platforms[10].y = 40;

		game::platforms[11].x = 97;
		game::platforms[11].y = 40;

		//top right
		game::platforms[12].x = 209;
		game::platforms[12].y = 40;

		game::platforms[13].x = 225;
		game::platforms[13].y = 40;

		game::platforms[14].x = 241;
		game::platforms[14].y = 40;

		game::platforms[15].x = 257;
		game::platforms[15].y = 40;

		Player1.init();
	}

	//game::mainLoop
	//The main loop for ingame
	//Parameters: None
	//Return: None
	void mainLoop()
	{
		bticks = SDL_GetTicks();

		//calc fps
		ShownFrames++;
		if((SDL_GetTicks() - LastTime) >= 1000)
		{
			printf("%li\n", ShownFrames);
	 
			ShownFrames = 0;
			LastTime = SDL_GetTicks();
		}
		//draw the platforms
		drawLevel();
		
		//update player 1
		Player1.update();
		
		video::switchBuf();

		//clear the screen
		SDL_FillRect(video::screen, &video::screen->clip_rect, SDL_MapRGB(video::screen->format, 0, 0, 0)); 

		//limit the framerate
		cticks = SDL_GetTicks();
		if ((cticks - bticks) < wait){
			//framerate exceeded limit....so we wait the difference
			//SDL_Delay(wait - (cticks - bticks));
		}

		return;
	}

	//game::drawLevel
	//Draws all the platforms, ropes and emmiters
	//Parameters: None
	//Return: None
	void drawLevel()
	{
		for (char i = 0; i < 16; i++){
			SDL_BlitSurface(video::images[video::platform], &video::images[video::platform]->clip_rect, video::screen, &game::platforms[i]);
			game::platforms[i].h = 1;
		}
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
