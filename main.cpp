#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "video.hpp"
#include "game.hpp"
#include "menu.hpp"
#include "main.hpp"

char currState = 1;
bool running = true;
SDL_Event events;
char theme[32];
game Game;

/*
* the start of the game
* Param: number of command line args, the command line args. Auto filled on startup
*/
int main(int argc, char *argv[])
{
	//register SDL_Quit to run when exit() is run
	atexit(SDL_Quit);

	//theme. using main as the theme
	sprintf(theme, "main");

	//init SDL
	video::init();

	//get the game setup
	//TODO! when menu works move this to the menu
	Game.init();

	//main loop
	
	mainLoop();

	exit(0);
}
/*
*the main loop for the game
*/
void mainLoop()
{
	while (running){
		//check for quit
		while(SDL_PollEvent(&events)){
			switch(events.type){
				case SDL_QUIT:
					running = false;
					break;
			}
		}

		switch(currState)
		{
			case inMenu:
				menu::mainLoop();
				break;
			case inGame:
				Game.mainLoop();
				break;
		}
	}
}
