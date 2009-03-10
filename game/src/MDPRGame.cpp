#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Clock.hpp>
#include "menu/GUI/window.hpp"
#include <boost/program_options.hpp>
//#include <boost/python/exec.hpp>
//#include <boost/python.hpp>
#include <iostream>
#include <fstream>
#include "MDPRGame.hpp"
#include "sprite/player.hpp"
#include "network/networkClient.hpp"
#include "menu/menuManager.hpp"
#include "sprite/spriteManager.hpp"
#include "sprite/player.hpp"
#include "sprite/platform.hpp"
#include "sprite/bubble.hpp"
#include "sprite/powerup.hpp"
#include "sprite/deathArea.hpp"
#include "menu/GUI/clickable.hpp"

//sf::RenderWindow App;
boost::shared_ptr<MDPRGame> MDPR;

int main(int argc, char** argv)
{
	try {
		/*using namespace boost::python;
		Py_Initialize();

		// Retrieve the main module.
		object mainModule = import("__main__");
		

		// Retrieve the main module's namespace
		object global = mainModule.attr("__dict__");
		global["genericPowerUp"] = class_<genericPowerUp>("genericPowerUp").def("getNum", &genericPowerUp::getNum);
		
		
		//CppClass asfd;
		//global["cpp"] = ptr(&asfd);
		//Load the greet function from a file.
		//
		object result = exec_file("data/mdpr/sprites/player/gun.py", global, global);*/
		






		// Set display mode
		sf::WindowSettings test(24,8,16);
		//test.AntialiasingLevel 8;
		sf::RenderWindow App;
		App.Create(sf::VideoMode(640, 400, 32), "Marshmallow Duel: Percy's Return", sf::Style::Resize | sf::Style::Close, test);
		App.EnableKeyRepeat(false);
		boost::shared_ptr<MDPRGame> newMDPR(new MDPRGame(App));
		MDPR = newMDPR;

		boost::shared_ptr<menuManager> newMenu(new menuManager);
		menu = newMenu;

		MDPR->run();
	}catch (std::exception& e){
		std::cout << "Exception: " << e.what() << std::endl;
	}/*catch( boost::python::error_already_set ) {
		PyErr_Print();
	}*/
	return 0;
}

bool MDPRGame::quit = false;

MDPRGame::MDPRGame(sf::RenderWindow &App)
	:	App(App),
		playerName("No Name"),
		serverIP("24.85.77.75"),
		serverPort("9935")
{
	//std::string playerName;
	boost::program_options::options_description config("Configuration");
	config.add_options()
		("playerName",		boost::program_options::value<std::string>(&playerName),"")
		("serverIP",		boost::program_options::value<std::string>(&serverIP), 	"");

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


	/*{
		Player player("Player");
		Platform platform("Platform");
		Bubble bubble("Bubble");
		PowerUp powerup("Powerup");
		DeathArea death("Death", sf::IntRect());
	}*/

	sprite.setActive(true);

	//boost::shared_ptr<Network::Client> networkClient(new Network::Client);
	//networkClient->run();

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
				//networkClient->sendKeyPress(Event.Key.Code, true);
			}else if (Event.Type == sf::Event::KeyReleased){
				//networkClient->sendKeyPress(Event.Key.Code, false);
			}else if(Event.Type == sf::Event::MouseButtonPressed){
				GUI::clickable::mouseDown();
			}else if(Event.Type == sf::Event::MouseButtonReleased){
				GUI::clickable::mouseUp();
			}

		}

		//if (menu->isActive()){
			menu->update();
		//}
		//test.draw();


		//network->update();

        if (sprite.isActive()){
			boost::mutex::scoped_lock lock(sprite.spriteMutex);
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

void MDPRGame::quitGame()
{
	quit = true;
}
