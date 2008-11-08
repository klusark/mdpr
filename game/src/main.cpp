#include "engine/engineAll.hpp"
//#include <iostream>
//#include "player.hpp"
#include <vector>
int main()
{
	try{
		engine::initEngine();

		if (!engine::window::createWindow(320, 200, 32, "Marshmallow Duel: Percy's Return", 0)){
			return 0;
		}
		//load the images
		std::vector<std::string> images;
		images.push_back("run0");images.push_back("run1");images.push_back("run2");images.push_back("run3");
		engine::graphics::loadImage(".png", "data/main/", images);


		//setup the player
		engine::Sprite *player = new engine::Sprite("player1");
		engine::spriteInterface *playerAnimation = new engine::Animation;
		engine::spriteInterface *playerMovement = new engine::Movement;
		engine::spriteInterface *playerMass = new engine::Mass;
		engine::spriteInterface *playerInput = new engine::Input;
		engine::spriteInterface *playerCollision = new engine::Collision;
		
		dynamic_cast<engine::Animation*>(playerAnimation)->makeAnimation("run", 4, 100, "run0", "run1", "run2", "run3");
		dynamic_cast<engine::Animation*>(playerAnimation)->changeAnimation("run");
		player->addInterface(playerAnimation);
		player->addInterface(playerMovement);
		player->addInterface(playerMass);
		player->addInterface(playerInput);
		player->addInterface(playerCollision);
		engine::spriteManager::registerSprite(player);

	
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
