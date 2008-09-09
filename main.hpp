#ifndef main_h
#define main_h

enum States
{
	inMenu,
	inGame,
};

extern void mainLoop();
extern char currState;
extern bool running;
extern char theme[32];

#endif
