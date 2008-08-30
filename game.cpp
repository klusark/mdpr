#include "game.h"

player Player1;
Uint32 LastTime = SDL_GetTicks();
unsigned int ShownFrames = 0;
void game::init()
{
	Player1.init();
}

void game::mainLoop()
{


	ShownFrames++;
 
    if((SDL_GetTicks() - LastTime) >= 1000)
    {
		printf("%li\n",ShownFrames);
 
        ShownFrames = 0;
        LastTime = SDL_GetTicks();
    }

	getInput();
	Player1.update();
	SDL_Flip(video::screen);
	return;
}

int game::getInput()
{
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		switch(event.type){
			case SDL_QUIT:
				running = 0;
				break;
		}
	}
	return 0;
}