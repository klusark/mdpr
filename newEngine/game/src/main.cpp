#include "engine/engineAll.hpp"
#include "stdio.h"
int main()
{
	engine::initEngine();

	if (!engine::window::createWindow(200, 200, 32, "test", 0)){
		return 0;
	}

	try{
		while (1){
			engine::eventLoop();
			engine::mainLoop();
		}
	}catch(int exception){
	}

	engine::quit();
	return 1;
}