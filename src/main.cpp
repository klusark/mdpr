#include "SDL.h"

#include "GameManager.hpp"

/**
 * Main function for the game
 */
int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Surface *screen = SDL_SetVideoMode(320, 200, 32, SDL_HWSURFACE |SDL_HWACCEL | SDL_DOUBLEBUF);

	SDL_WM_SetCaption("Marshmallow Duel: Percy's Return", "Marshmallow Duel: Percy's Return");
	Uint32 frames = 0, lastTime = 0;
	GameManager *gm = new GameManager(screen);

	//main loop
	gm->activate();
	try
	{
		//go untill an exception is raised
		for (;;){
			SDL_Event events;
			while (SDL_PollEvent(&events)){
				if (events.type == SDL_QUIT){
					//quit the game
					throw 1; 
				}
			}
			if (gm->isActive()){
				gm->tick();
			}
			if (SDL_GetTicks()-lastTime > 1000){
				lastTime = SDL_GetTicks();
				printf("%i\n",frames);
				frames = 0;

			}
			++frames;
		}
	} catch(int exception) {
		delete gm;
		return exception;
	}
}
/*! \mainpage Marshmallow Duel: Percy's Return
*/
