#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
//#include <SFML/Window/Window.hpp>
#include "menu/GUI/window.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include "MDPRGame.hpp"
#include "sprite/player.hpp"
#include "network/networkClient.hpp"
#include "menu/menuManager.hpp"
#include "sprite/spriteManager.hpp"
#include "sprite/player.hpp"

sf::RenderWindow App;
MDPRGame MDPR(App);

int main(int argc, char** argv)
{
	try {
		// Set display mode
		App.Create(sf::VideoMode(640, 400, 32), "Marshmallow Duel: Percy's Return");
		App.EnableKeyRepeat(false);
		MDPR.run();
	}catch (std::exception& e){
		std::cout << "Exception: " << e.what() << std::endl;
	}
	return 0;
}


MDPRGame::MDPRGame(sf::RenderWindow &App)
	:	App(App),
		quit(false),
		playerName("No Name"),
		serverIP("24.85.77.75"),
		serverPort("9935")
{
	//std::string playerName;
	boost::program_options::options_description config("Configuration");
	config.add_options()
		//("animation",	boost::program_options::value<std::vector<std::string> >(&animations), "")
		("playerName",		boost::program_options::value<std::string>(&playerName), "");

	boost::program_options::variables_map configVariableMap;

	boost::program_options::options_description configFileOptions;
	configFileOptions.add(config);
	
	std::ifstream configFileStream("conf");

	boost::program_options::store(parse_config_file(configFileStream, configFileOptions), configVariableMap);
	notify(configVariableMap);
}

MDPRGame::~MDPRGame()
{
}

void MDPRGame::run()
{
	//Player *player = new Player;
	static int Frames = 0;
	float seconds, fps = 0;


	boost::shared_ptr<genericSprite> Sprite(new Player("Player"));

	//boost::shared_ptr<spriteManager> tmpSprite(new spriteManager);
	//sprite = tmpSprite;

	sprite.setActive(true);

	boost::shared_ptr<Network::Client> networkClient(new Network::Client);
	networkClient->run();
	GUI::window test(540,300,50,50);

	while(!quit)
	{
		App.Clear();
		sf::Event Event;
		while (App.GetEvent(Event)){
			// Window closed
			if (Event.Type == sf::Event::Closed){
				quit = true;
			}

			if (Event.Type == sf::Event::KeyPressed){
				networkClient->sendKeyPress(Event.Key.Code, true);
			}
			if (Event.Type == sf::Event::KeyReleased){
				networkClient->sendKeyPress(Event.Key.Code, false);
			}
		}

		//if (menu->isActive()){
			//menu.update();
		//}
		//test.draw();


		//network->update();

        if (sprite.isActive()){
			sprite.update();
			sprite.draw(App);


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

		*/

		App.Display();
	}
}
