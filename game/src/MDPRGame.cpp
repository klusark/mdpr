#include <SFML/System/Sleep.hpp>
#include <SFML/System/Clock.hpp>

//#include <boost/program_options.hpp>
//#include <boost/thread.hpp>
#include <iostream>
#include <fstream>
#include <time.h>
#include <Poco/RunnableAdapter.h>

#include "network/networkClient.hpp"
#include "menu/menuManager.hpp"
#include "sprite/clientSpriteManager.hpp"
#include "MDPRGame.hpp"

MDPRGame *MDPR;

/*int main(int argc, char** argv)
{
	try {
		// Set display mode
		sf::RenderWindow App;

		Poco::SharedPtr<MDPRGame> newMDPR(new MDPRGame(App));
		MDPR = newMDPR;

		MDPR->run();
	}catch (std::exception& e){
		std::cout << "Exception: " << e.what() << std::endl;
	}catch(gcn::Exception except){
		std::cout << except.getMessage() << std::endl;
	}
	return 0;
}*/

POCO_APP_MAIN(MDPRGame)

bool MDPRGame::quit = false;

MDPRGame::MDPRGame()
	:	userInterface(false)
{
	
}

void MDPRGame::initialize(Poco::Util::Application& self)
{
	loadConfiguration();
	Poco::Util::Application::initialize(self);
}

void MDPRGame::uninitialize()
{
}

MDPRGame::~MDPRGame()
{
	//delete myNetworkClient;
}

int MDPRGame::main(const std::vector<std::string>& args)
{
	/*{
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
		if (!configFileStream.is_open()){
			return;
		}

		boost::program_options::store(parse_config_file(configFileStream, configFileOptions), configVariableMap);
		notify(configVariableMap);
	}*/
	MDPR = this;
	App.Create(sf::VideoMode(config().getInt("graphics.width"), config().getInt("graphics.height"), config().getInt("graphics.bpp")), "Marshmallow Duel: Percy's Return", sf::Style::Close, sf::WindowSettings(24, 8, config().getInt("graphics.antialiasing")));
	App.EnableKeyRepeat(false);
	App.UseVerticalSync(config().getBool("graphics.VerticalSync"));

	//myNetworkClient = new NetworkClient;
	//Poco::SharedPtr<NetworkClient> newClient(new NetworkClient);
	myNetworkClient.assign(new NetworkClient);// = newClient;
	myNetworkClient->connectToMaster();

	Poco::SharedPtr<menuManager> newMenu(new menuManager(App));
	menu = newMenu;

	sprite.setActive(true);

	App.SetActive(false);

	Poco::RunnableAdapter<MDPRGame> drawThreadAdapter(*this, &MDPRGame::drawThread);
	pool.start(drawThreadAdapter);
	Poco::RunnableAdapter<MDPRGame> updateThreadAdapter(*this, &MDPRGame::updateThread);
	pool.start(updateThreadAdapter);

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
			}else{
				menu->currentMenu->input.pushEvent(Event, App.GetInput());
			}

		}
		sf::Sleep(0.001f);
		
	}
	pool.joinAll();
	App.SetActive(true);
	return Application::EXIT_OK;
}

void MDPRGame::quitGame()
{
	quit = true;
}

void MDPRGame::drawThread()
{
	try {
		App.SetActive(true);
		int Frames = 0;
		float seconds, fps = 0;

		while (!quit){

			App.Clear(sf::Color(0,0,0));


			if (sprite.isActive()){
				Poco::ScopedLock<Poco::Mutex> lock(sprite.spriteMutex);
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
			//if (menu->isActive()){
				menu->draw();
			//}
			App.Display();
			//sf::Sleep(0.01f);
		}
	}catch(gcn::Exception except){
		std::cout << except.getMessage() << std::endl;
	}catch (std::exception& e){
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

void MDPRGame::updateThread()
{
	try {
		while (!quit){

			menu->logic();
			if (sprite.isActive()){
				Poco::ScopedLock<Poco::Mutex> lock(sprite.spriteMutex);
				sprite.update();
			}
			sf::Sleep(0.003f);
		}
	}catch(gcn::Exception except){
		std::cout << except.getMessage() << std::endl;
	}catch (std::exception& e){
		std::cout << "Exception: " << e.what() << std::endl;
	}
}