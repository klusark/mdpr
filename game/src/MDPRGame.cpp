#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <boost/program_options.hpp>
#include <boost/thread.hpp>
#include <WebCore.h>
#include <iostream>
#include <fstream>

#include "sprite/player.hpp"
#include "network/networkClient.hpp"
//#include "menu/menuManager.hpp"
#include "sprite/spriteManager.hpp"
#include "sprite/player.hpp"
#include "sprite/platform.hpp"
#include "sprite/bubble.hpp"
#include "sprite/powerup.hpp"
#include "sprite/deathArea.hpp"
#include "MDPRGame.hpp"
#include "WebViewListener.hpp"


#define WIDTH 640
#define HEIGHT 400
//sf::RenderWindow App;
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
		userInterface(false)
{
	{
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
	App.Create(sf::VideoMode(WIDTH, HEIGHT, 32), "Marshmallow Duel: Percy's Return", sf::Style::Close, sf::WindowSettings(24, 8, 0));
	App.EnableKeyRepeat(false);
	App.UseVerticalSync(true);
	
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
	std::map<unsigned int, unsigned int> SFMLKToVK;
	SFMLKToVK[sf::Key::Back] = VK_BACK;
	SFMLKToVK[sf::Key::Return] = VK_RETURN;
	SFMLKToVK[sf::Key::RShift] = VK_SHIFT;
	SFMLKToVK[sf::Key::LShift] = VK_SHIFT;
	boost::shared_ptr<Awesomium::WebCore> newWebCore(new Awesomium::WebCore(Awesomium::LOG_NORMAL, false, Awesomium::PF_RGBA));
	webCore = newWebCore;

	webView = webCore->createWebView(WIDTH, HEIGHT, false, false);
	webView->loadFile("menu.html");
	WebViewListener* myListener = new WebViewListener();
	webView->setListener(myListener);
	webView->setCallback("Quit");
	webView->setCallback("populateResolution");


	//menu->setActive(false);
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
			}else if (Event.Type == sf::Event::MouseMoved){
				webView->injectMouseMove(Event.MouseMove.X, Event.MouseMove.Y);
			}else if(Event.Type == sf::Event::MouseButtonPressed){
				if (Event.MouseButton.Button == sf::Mouse::Left){
					webView->injectMouseDown(Awesomium::LEFT_MOUSE_BTN);
				}else if (Event.MouseButton.Button == sf::Mouse::Right){
					webView->injectMouseDown(Awesomium::RIGHT_MOUSE_BTN);
				}
			}else if(Event.Type == sf::Event::MouseButtonReleased){
				if (Event.MouseButton.Button == sf::Mouse::Left){
					webView->injectMouseUp(Awesomium::LEFT_MOUSE_BTN);
				}else if (Event.MouseButton.Button == sf::Mouse::Right){
					webView->injectMouseUp(Awesomium::RIGHT_MOUSE_BTN);
				}
			}else if (Event.Type == sf::Event::KeyPressed){

				unsigned int key = Event.Key.Code;
				if (SFMLKToVK.find(Event.Key.Code) != SFMLKToVK.end()){
					key = SFMLKToVK[Event.Key.Code];
				}
				
				webView->injectKeyboardEvent(0, WM_CHAR, key, 0);
				webView->injectKeyboardEvent(0, WM_KEYDOWN, key, 0);

			}else if (Event.Type == sf::Event::KeyReleased){
				webView->injectKeyboardEvent(0, WM_KEYUP, Event.Key.Code, 0);

				
			}

			if (myNetworkClient->connected){
				if (Event.Type == sf::Event::KeyPressed){
					myNetworkClient->sendKeyPress(Event.Key.Code, true);
				}else if (Event.Type == sf::Event::KeyReleased){
					myNetworkClient->sendKeyPress(Event.Key.Code, false);
				}
			}

		}
		sf::Sleep(0.0001f);
		
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
	App.SetActive(true);
	static int Frames = 0;
	float seconds, fps = 0;
	unsigned char* buffer = new unsigned char[WIDTH * HEIGHT * 4];
	unsigned int texture;
	//App.Clear(sf::Color(255,0,0));
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);



	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	webView->render(buffer, WIDTH*4, 4);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);


	
	//newsprite.SetImage(image);
	while (!quit){

		App.Clear(sf::Color(0,0,0));
		/*if (menu->isActive()){
			boost::mutex::scoped_lock lock(menu->menuMutex);
			menu->draw();
		}*/

		if (sprite.isActive()){
			boost::mutex::scoped_lock lock(sprite.spriteMutex);
			sprite.draw(App);
		}
		if (userInterface){
			if (!quit && webView->isDirty()){
				webView->render(buffer, WIDTH*4, 4);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(GL_TEXTURE_2D, 0, 4, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
				glBegin(GL_QUADS);
					glTexCoord2i(0, 0); glVertex2i(0, 0);
					glTexCoord2i(1, 0); glVertex2i(WIDTH, 0);
					glTexCoord2i(1, 1); glVertex2i(WIDTH, HEIGHT);
					glTexCoord2i(0, 1); glVertex2i(0, HEIGHT);
				glEnd();
			}
		}
		Frames++;
		seconds = Clock.GetElapsedTime();
		if (seconds >= 5) {

			fps = Frames / seconds;
			std::cout << Frames << " frames in " << seconds << " seconds = " << fps << " FPS" << std::endl;

			MDPR->Clock.Reset();
			Frames = 0;
		}
		
		App.Display();
		//sf::Sleep(0.001f);
	}
}

void MDPRGame::updateThread()
{
	while (!quit){
		/*if (menu->isActive()){
			boost::mutex::scoped_lock lock(menu->menuMutex);
			menu->update();
		}*/
		webCore->update();
		if (sprite.isActive()){
			boost::mutex::scoped_lock lock(sprite.spriteMutex);
			sprite.update();
		}
		sf::Sleep(0.001f);
	}
}