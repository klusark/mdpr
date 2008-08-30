#include "main.hpp"

short currState = 1;
bool running = true;
int main(int argc, char *argv[])
{
	atexit(SDL_Quit);
	
	video::init();
	game::init();
	//main loop
	while (running){
		switch(currState)
		{
		case inMenu:
			break;
		case inGame:
			game::mainLoop();
			break;
		}
	}
	exit(0);
	return 0;
}
