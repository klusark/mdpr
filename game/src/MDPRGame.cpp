#include <SFML/System/Sleep.hpp>
#include <SFML/System/Clock.hpp>

#include <iostream>
#include <Poco/RunnableAdapter.h>
#include <Poco/Util/PropertyFileConfiguration.h>

#include "network/networkClient.hpp"
#include "menu/menuManager.hpp"
#include "sprite/clientSpriteManager.hpp"
#include "MDPRGame.hpp"
#include "helpers.hpp"

MDPRGame *MDPR;

//must implement it this way because poco does not like to seem win main...
int main(int argc, char** argv)
{
	Poco::AutoPtr<MDPRGame> pApp = new MDPRGame;
	try{						
		pApp->init(argc, argv);	
	}catch (Poco::Exception& exc){
		pApp->logger().log(exc);
		return Poco::Util::Application::EXIT_CONFIG;
	}
	return pApp->run();
}

bool MDPRGame::quit = false;

MDPRGame::MDPRGame()
	:	userInterface(false)
{
	
}

void MDPRGame::initialize(Poco::Util::Application& self)
{
	propertyFile.assign(new Poco::Util::PropertyFileConfiguration);
	propertyFile->load("mdpr.properties");
	config().add(propertyFile, 0, false, true);
	Poco::Util::Application::initialize(self);
}

void MDPRGame::uninitialize()
{
}

MDPRGame::~MDPRGame()
{
}

int MDPRGame::main(const std::vector<std::string>& args)
{
	controls.up =		config().getString("mdpr.player1.controls.up").c_str()[0];
	controls.down =		config().getString("mdpr.player1.controls.down").c_str()[0];
	controls.left =		config().getString("mdpr.player1.controls.left").c_str()[0];
	controls.right =	config().getString("mdpr.player1.controls.right").c_str()[0];
	controls.use =		config().getString("mdpr.player1.controls.use").c_str()[0];

	propertyFile->setInt("stats.TotalTimesRun", propertyFile->getInt("stats.TotalTimesRun", 0)+1);
	MDPR = this;

	//Clear
	App.Clear();

	App.Create(sf::VideoMode(config().getInt("graphics.width"), config().getInt("graphics.height"), config().getInt("graphics.bpp")), "Marshmallow Duel: Percy's Return", sf::Style::Close|sf::Style::Resize, sf::WindowSettings(24, 8, config().getInt("graphics.antialiasing")));
	App.Clear();
	lastWidth = 0;
	lastHeight = 0;
	
	//Then display it that that the screen is black when loading.
	App.Display();

	
	App.SetView(view);
	App.EnableKeyRepeat(false);
	App.UseVerticalSync(config().getBool("graphics.VerticalSync"));
	App.SetFramerateLimit(config().getInt("graphics.FrameLimit"));

	menu.assign(new MenuManager(App));
	menu->setActive(true);

	profileManager.assign(new ProfileManager);

	myNetworkClient.assign(new NetworkClient);
	myNetworkClient->connectToMaster();


	sprite.assign(new ClientSpriteManager);

	sprite->setActive(true);

	App.SetActive(false);

	Poco::RunnableAdapter<MDPRGame> drawThreadAdapter(*this, &MDPRGame::drawThread);
	pool.start(drawThreadAdapter);
	Poco::RunnableAdapter<MDPRGame> updateThreadAdapter(*this, &MDPRGame::updateThread);
	pool.start(updateThreadAdapter);


	sf::Event Event;
	while(!quit)
	{
		
		while (App.GetEvent(Event)){
			// Window closed
			if (Event.Type == sf::Event::Closed){
				//Set quit to true causing all the threads to exit
				quit = true;
			}

			if (profileManager->isConnected()){
				if (Event.Type == sf::Event::KeyPressed){
					profileManager->sendKeyPress(Event.Key.Code, true);
				}else if (Event.Type == sf::Event::KeyReleased){
					profileManager->sendKeyPress(Event.Key.Code, false);
				}
			}else{
				menu->handleEvent(Event);
			}

		}
		sf::Sleep(0.001f);
		
	}
	pool.joinAll();
	App.SetActive(true);
	propertyFile->save("mdpr.properties");
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
		unsigned int mySpriteID = stringToCRC(Poco::Util::Application::instance().config().getString("mdpr.playerName"));
		bool found = false;
		ClientSprite* mySprite;

		while (!quit){

			App.Clear(sf::Color(0,0,0));

			if (sprite->isActive()){
				Poco::ScopedLock<Poco::Mutex> lock(sprite->spriteMutex);
				
				if (found){
					sf::Vector2f test = (mySprite->GetPosition() - view.GetCenter()) + sf::Vector2f(12,12);
					view.Move(test);
				}else if ((sprite->Sprites.find(mySpriteID) != sprite->Sprites.end())){
					found = true;
					mySprite = sprite->Sprites[mySpriteID].get();
				}
				sprite->draw(App);
				
			}

			Frames++;
			seconds = Clock.GetElapsedTime();
			if (seconds >= 5){
				fps = Frames / seconds;
				std::cout << Frames << " frames in " << seconds << " seconds = " << fps << " FPS" << std::endl;

				Clock.Reset();
				Frames = 0;
			}
			if (menu->isActive()){
				App.SetView(App.GetDefaultView());
				menu->draw();
				App.SetView(view);
			}

			App.Display();
			//sf::Sleep(0.01f);
		}
	}catch (std::exception& e){
		logger().error(e.what());
		//std::cout << "Exception: " << e.what() << std::endl;
	}
}

void MDPRGame::updateThread()
{
	int Frames = 0;
	try {
		float seconds, fps = 0;
		sf::Clock clock;

		unsigned int mySpriteID = stringToCRC(Poco::Util::Application::instance().config().getString("mdpr.playerName"));

		while (!quit){
			Frames++;
			seconds = clock.GetElapsedTime();
			if (seconds >= 5){
				fps = Frames / seconds;
				std::cout << Frames << " updates in " << seconds << " seconds = " << fps << " UPS" << std::endl;

				clock.Reset();
				Frames = 0;
			}
			if (sprite->isActive()){
				Poco::ScopedLock<Poco::Mutex> lock(sprite->spriteMutex);
				sprite->update();
			}

			unsigned int currentWidth = App.GetWidth(), currentHeight = App.GetHeight();
			if (lastWidth != currentWidth || lastHeight != currentHeight){
				lastWidth = currentWidth;
				lastHeight = currentHeight;

				float currentRatio = (float)currentWidth/(float)currentHeight;
				float correctY = 640/currentRatio;

				view.SetFromRect((sf::FloatRect(0, 0, 640, correctY)));

				/*if (sprite->Sprites.find(mySpriteID) != sprite->Sprites.end()){
					view.SetCenter(sprite->Sprites[mySpriteID]->GetPosition() + Vector);
				}*/
				view.Zoom(1.0f);

				if (menu->isActive()){
					menu->resize((float)currentWidth, (float)currentHeight);
				}
				
			}

			sf::Sleep(0.01f);
		}
	}catch (std::exception& e){
		logger().error(e.what());
		//std::cout << "Exception: " << e.what() << std::endl;
	}
}
