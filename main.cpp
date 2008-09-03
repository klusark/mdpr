#include "main.hpp"

short currState = 1;
bool running = true;
SDL_Event events;
char theme[32];


//main
//the start of the game
//Parameters: number of command line args, the command line args
//Return: None
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
	game::init();

	//main loop
	mainLoop();

	exit(0);
}

//mainLoop
//the main loop for the game
//Parameters: None
//Return: None
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
				game::mainLoop();
				break;
		}
	}
	return;
}