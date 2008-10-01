#include "SDL/SDL.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <stdio.h>

#include <time.h>

#include "GameManager.hpp"

#include <string>

/**
 * Main function for the game
 */
int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	lua_State *luaState = lua_open();
	luaL_openlibs(luaState);
	if (luaL_loadfile(luaState, "config.lua") || lua_pcall(luaState, 0, 0, 0))
	{
		printf("error: %s\n", lua_tostring(luaState, -1));
		return -1;
	}
	lua_getglobal(luaState, "height");
    lua_getglobal(luaState, "width");
	int height = (int)lua_tonumber(luaState, -2);
	int width = (int)lua_tonumber(luaState, -1);
	if ((double)width/(double)height != 1.6){
		printf("error: the width and height are not correct");
		return -1;
	}
	int scale = width/320;
	SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE |SDL_HWACCEL | SDL_DOUBLEBUF);
	GameManager *gm = new GameManager(screen, width, height, luaState);
	SDL_WM_SetCaption("Marshmallow Duel: Percy's Return", "Marshmallow Duel: Percy's Return");
	Uint32 frames = 0, lastTime = 0;

	srand ( (unsigned) time(NULL) );

	printf("Loading Time: %li Ms\n", SDL_GetTicks());
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
	} catch(int) {
		
		//return exception;
	} catch(char *message) {
		printf("%s", message);
		SDL_Delay(1000);
	}
	delete gm;
	SDL_FreeSurface(screen);
	lua_close(luaState);
	SDL_Quit();
	return 0;
}
/** \mainpage Marshmallow Duel: Percy's Return
*/
