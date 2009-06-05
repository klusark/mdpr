#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <boost/program_options.hpp>
#include <boost/thread.hpp>
#include <boost/random.hpp>
#include <iostream>
#include <fstream>
#include <time.h>


#include "sprite/player.hpp"
#include "network/networkClient.hpp"
#include "menu/menuManager.hpp"
#include "sprite/spriteManager.hpp"
#include "sprite/player.hpp"
#include "sprite/platform.hpp"
#include "sprite/bubble.hpp"
#include "sprite/powerup.hpp"
//#include "sprite/deathArea.hpp"
#include "MDPRGame.hpp"


boost::shared_ptr<MDPRGame> MDPR;

int main(int argc, char** argv)
{
	try {
		// Set display mode
		sf::RenderWindow App;

		boost::shared_ptr<MDPRGame> newMDPR(new MDPRGame(App));
		MDPR = newMDPR;

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
		serverPort("9935"),
		height(400),
		width(640),
		userInterface(false)
{
	
	{
		
		boost::program_options::options_description config("Configuration");
		config.add_options()
			("playerName",		boost::program_options::value<std::string>(&playerName),"")
			("serverIP",		boost::program_options::value<std::string>(&serverIP), 	"")
			("width",			boost::program_options::value<unsigned int>(&width), 	"")
			("height",			boost::program_options::value<unsigned int>(&height), 	"")
			("controls.up",		boost::program_options::value<char>(&controls.up),		"")
			("controls.down",	boost::program_options::value<char>(&controls.down), 	"")
			("controls.left",	boost::program_options::value<char>(&controls.left), 	"")
			("controls.right",	boost::program_options::value<char>(&controls.right), 	"")
			("controls.use",	boost::program_options::value<char>(&controls.use),	"");

		boost::program_options::variables_map configVariableMap;

		boost::program_options::options_description configFileOptions;
		configFileOptions.add(config);

		std::ifstream configFileStream("conf");

		boost::program_options::store(parse_config_file(configFileStream, configFileOptions), configVariableMap);
		notify(configVariableMap);
	}
	App.Create(sf::VideoMode(width, height, 32), "Marshmallow Duel: Percy's Return", sf::Style::Close, sf::WindowSettings(24, 8, 0));
	App.EnableKeyRepeat(false);
	//App.UseVerticalSync(true);
	//App.SetFramerateLimit(25);
	
	
}

MDPRGame::~MDPRGame()
{
	//delete myNetworkClient;
}

void MDPRGame::run()
{
	/*{
		Player player("Player");
		Platform platform("Platform");
		Bubble bubble("Bubble");
		PowerUp powerup("Powerup");
		DeathArea death("Death", sf::IntRect());
	}*/

	boost::shared_ptr<menuManager> newMenu(new menuManager(App));
	menu = newMenu;

	sprite.setActive(true);

	
	myNetworkClient = new networkClient;
	myNetworkClient->connect();
	
	App.SetActive(false);

	boost::thread_group Threads;
	Threads.create_thread(boost::bind(&MDPRGame::updateThread, this));
	Threads.create_thread(boost::bind(&MDPRGame::drawThread, this));

	while(!quit)
	{
		
		sf::Event Event;
		
		while (App.GetEvent(Event)){
			// Window closed
			if (Event.Type == sf::Event::Closed){
				quit = true;
			}

			if (myNetworkClient->connected){
				if (Event.Type == sf::Event::KeyPressed){
					myNetworkClient->sendKeyPress(Event.Key.Code, true);
				}else if (Event.Type == sf::Event::KeyReleased){
					myNetworkClient->sendKeyPress(Event.Key.Code, false);
				}
			}
			//menu->currentMenu->input.pushEvent(Event, App.GetInput());

		}
		sf::Sleep(0.001f);
		
	}
	delete myNetworkClient;
	Threads.join_all();
	App.SetActive(true);
}

void MDPRGame::quitGame()
{
	quit = true;
}

void MDPRGame::drawThread()
{
	try {
		App.SetActive(true);
		static int Frames = 0;
		float seconds, fps = 0;

		while (!quit){

			App.Clear(sf::Color(0,0,0));


			if (sprite.isActive()){
				boost::mutex::scoped_lock lock(sprite.spriteMutex);
				sprite.draw(App);
			}

			Frames++;
			seconds = Clock.GetElapsedTime();
			if (seconds >= 5) {

				fps = Frames / seconds;
				std::cout << Frames << " frames in " << seconds << " seconds = " << fps << " FPS" << std::endl;

				MDPR->Clock.Reset();
				Frames = 0;
			}
			
			menu->draw();
			App.Display();
			//sf::Sleep(0.001f);
		}
	}catch(gcn::Exception except){

	}
}

void MDPRGame::updateThread()
{
	try {
		while (!quit){

			menu->logic();
			if (sprite.isActive()){
				boost::mutex::scoped_lock lock(sprite.spriteMutex);
				sprite.update();
			}
			sf::Sleep(0.001f);
		}
	}catch(gcn::Exception except){

	}
}