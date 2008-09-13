#ifndef main_h
#define main_h
#include "game.hpp"

enum States
{
	inMenu,
	inGame,
};

extern game Game;

extern void mainLoop();
extern char currState;
extern bool running;
extern char theme[32];

#endif
