#include "game.hpp"

namespace game
{
	SDL_Rect platforms[4];
	player Player1;
	Uint32 LastTime = SDL_GetTicks();
	unsigned int ShownFrames = 0;
	void init()
	{
		Player1.init();
	}

	void mainLoop()
	{
		ShownFrames++;
	 
		if((SDL_GetTicks() - LastTime) >= 1000)
		{
			printf("%li\n",ShownFrames);
	 
			ShownFrames = 0;
			LastTime = SDL_GetTicks();
		}
		SDL_FillRect(video::screen, &video::screen->clip_rect, SDL_MapRGB(video::screen->format, 0, 0, 0)); 
		getInput();
		drawPlatforms();
		Player1.update();
		video::switchBuf();
		return;
	}

	void getInput()
	{
		SDL_Event event;

		while(SDL_PollEvent(&event)) {
			switch(event.type){
				case SDL_QUIT:
					running = 0;
					break;
			}
		}
		return;
	}

	void drawPlatforms()
	{
		
		platforms[0].x = 50;
		platforms[0].y = 100;
		SDL_BlitSurface(video::images[video::platform], 0, video::screen, &platforms[0]);
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
