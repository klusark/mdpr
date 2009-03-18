#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Clock.hpp>

#include <boost/program_options.hpp>
#include <boost/thread.hpp>
//#include <boost/python/exec.hpp>
//#include <boost/python.hpp>
#include <iostream>
#include <fstream>

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
#include "MDPRGame.hpp"

struct drawThread
{
public:
	void operator()(){
		MDPR->App.SetActive(true);
		static int Frames = 0;
		float seconds, fps = 0;
		while (!MDPR->quit){

			MDPR->App.Clear();
			if (menu->isActive()){
				boost::mutex::scoped_lock lock(menu->menuMutex);
				menu->draw();
			}

			if (sprite.isActive()){
				boost::mutex::scoped_lock lock(sprite.spriteMutex);
				sprite.draw(MDPR->App);


			}
			Frames++;
			seconds = MDPR->Clock.GetElapsedTime();
			if (seconds >= 5) {

				fps = Frames / seconds;
				std::cout << Frames << " frames in " << seconds << " seconds = " << fps << " FPS" << std::endl;

				MDPR->Clock.Reset();
				Frames = 0;
			}
			
			MDPR->App.Display();
		}
	}
};

struct updateThread
{
public:
	void operator()(){
		while (!MDPR->quit){
			if (menu->isActive()){
				boost::mutex::scoped_lock lock(menu->menuMutex);
				menu->update();
			}

			if (sprite.isActive()){
				boost::mutex::scoped_lock lock(sprite.spriteMutex);
				sprite.update();
			}
		}
	}
};

//sf::RenderWindow App;
boost::shared_ptr<MDPRGame> MDPR;

int main(int argc, char** argv)
{
	try {

		


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
	}
	return 0;
}

bool MDPRGame::quit = false;

MDPRGame::MDPRGame(sf::RenderWindow &App)
	:	App(App),
		playerName("No Name"),
		serverIP("127.0.0.1"),
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
	delete networkClient;
}

void MDPRGame::run()
{
	//Player *player = new Player;



	{
		Player player("Player");
		Platform platform("Platform");
		Bubble bubble("Bubble");
		PowerUp powerup("Powerup");
		DeathArea death("Death", sf::IntRect());
	}

	menu->setActive(true);
	sprite.setActive(false);

	
	networkClient = new Network::Client;
	
	App.SetActive(false);
	drawThreadPtr = new boost::thread(drawThread());
	updateThreadPtr = new boost::thread(updateThread());
	while(!quit)
	{
		
		sf::Event Event;
		
		while (App.GetEvent(Event)){
			// Window closed
			if (Event.Type == sf::Event::Closed){
				quit = true;
			}

			if (Event.Type == sf::Event::KeyPressed){
				networkClient->sendKeyPress(Event.Key.Code, true);
			}else if (Event.Type == sf::Event::KeyReleased){
				networkClient->sendKeyPress(Event.Key.Code, false);
			}else if(Event.Type == sf::Event::MouseButtonPressed){
				GUI::clickable::mouseDown();
			}else if(Event.Type == sf::Event::MouseButtonReleased){
				GUI::clickable::mouseUp();
			}

		}
		Sleep(1);
		


	}
	App.SetActive(true);
}

void MDPRGame::quitGame()
{
	quit = true;
}
