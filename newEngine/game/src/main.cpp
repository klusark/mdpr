#include "engine/engineAll.hpp"
#include "stdio.h"
#include "player.hpp"
int main()
{
	engine::initEngine();

	if (!engine::window::createWindow(320, 200, 32, "Marshmallow Duel: Percy's Return", 0)){
		return 0;
	}
	engine::graphics::loadImage(".png", "data/main/", "idle", "run0", 0);
	Player *player;
	player = new Player("player");
	//engine::Sprite *sprite = ;
	engine::spriteManager::registerSprite(dynamic_cast<engine::Sprite*>(player));
	
	try{
		for(;;){
			//engine::eventLoop();
			engine::mainLoop();
		}
	}catch(int exception){
		if (exception){
		}
	}
	
	engine::quit();
	return 1;
}
