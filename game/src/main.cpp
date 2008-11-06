#include "engine/engineAll.hpp"
//#include <iostream>
//#include "player.hpp"
int main()
{
	try{
		engine::initEngine();

		if (!engine::window::createWindow(320, 200, 32, "Marshmallow Duel: Percy's Return", 0)){
			return 0;
		}
		engine::graphics::loadImage(".png", "data/main/", "idle", "run0", "run1", "run2", "run3", 0);
		//Player *player;
		//player = new Player("player");
		//engine::Sprite *sprite = ;

		engine::Sprite *player = new engine::Sprite("player1");
		engine::spriteManager::registerSprite(player);
		//player
	
	
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
