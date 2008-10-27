#include "engine/engineAll.hpp"
#include "stdio.h"
int main()
{
	engine::initEngine();

	if (!engine::window::createWindow(320, 200, 32, "test", 0)){
		return 0;
	}

	try{
		for(;;){
			//engine::eventLoop();
			engine::mainLoop();
		}
	}catch(int exception){
		if (exception){
		}
	}
	engine::graphics::loadImage("set","asdf","asdf");
	engine::quit();
	return 1;
}