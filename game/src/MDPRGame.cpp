#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>

#include <iostream>

#include "MDPRGame.hpp"
#include "sprite/player.hpp"
#include "network/network.hpp"
#include "menu/menuManager.hpp"
#include "sprite/spriteManager.hpp"
#include "sprite/player.hpp"

MDPRGame::MDPRGame(sf::RenderWindow &App) : App(App), quit(false)
{
	
}

MDPRGame::~MDPRGame()
{

}

void MDPRGame::run()
{
	//Player *player = new Player;
	static int Frames = 0;
	float seconds, fps = 0;


	//boost::shared_ptr<menuManager> tmpMenu(new menuManager(resources));
	//menu = tmpMenu;
	//menu->setActive(false);
	boost::shared_ptr<genericSprite> Sprite(new Player("Player"));

	boost::shared_ptr<spriteManager> tmpSprite(new spriteManager);
	sprite = tmpSprite;

	sprite->setActive(true);
	
	boost::shared_ptr<Network> network(new Network);

	while(!quit)
	{

		//if (menu->isActive()){
		//	menu->update();
		//}


		//network->update();

        if (sprite->isActive()){
			sprite->update();
			sprite->draw(App);


		}

		
		Frames++;
		seconds = Clock.GetElapsedTime();
		if (seconds >= 5) {
			//seconds /= 5;

			fps = Frames / seconds;
			std::cout << Frames << " frames in " << seconds << " seconds = " << fps << " FPS" << std::endl;

			Clock.Reset();
			Frames = 0;
		}
		/*
		std::stringstream buf;
		buf << std::fixed << static_cast<int>(fps);
		std::string stringFPS = buf.str();

		font.draw(320-font.get_width(stringFPS), 0, stringFPS);

		CL_Display::flip();
		CL_System::sleep(2);

		CL_System::keep_alive();
		*/
		sf::Event Event;
		while (App.GetEvent(Event)){
			// Window closed
			if (Event.Type == sf::Event::Closed){
				quit = true;
			}
		}

		App.Display();
	}
}
void MDPRGame::onWindowClose()
{
	quit = true;

}
