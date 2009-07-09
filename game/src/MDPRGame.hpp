#ifndef MDPRGame_hpp
#define MDPRGame_hpp

#include "network/networkClient.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <Poco/SharedPtr.h>
#include <Poco/ThreadPool.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/PropertyFileConfiguration.h>

//!The main class for the game
/*!
Sets up and runs the game.
*/
class MDPRGame : public Poco::Util::Application
{
public:
	//!Constructor
	/*!
	\param App The render window for the game to use.
	*/
	MDPRGame();
	
	//!Deconstructor
	~MDPRGame();

	void initialize(Poco::Util::Application& self);
	void uninitialize();
	//!Contains the event loop, and it starts the threads for drawing and updating. 
	int main(const std::vector<std::string>& args);

	Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> propertyFile;
	
	//!Quits the game
	static void quitGame();
	
	//!Draws the game
	void drawThread();
	
	//!updates the sprites
	void updateThread();
	
	//!the render window collected though the constructor
	sf::RenderWindow App;
	
	//!The name of the player
	std::string playerName;
	
	//!The ip of the server to connect to
	std::string serverIP;
	
	//!The port to connect to
	std::string serverPort;

	Poco::ThreadPool pool;

	static bool quit;
	sf::Clock Clock;
	Poco::SharedPtr<NetworkClient> myNetworkClient;
	bool isRunning, userInterface;
	unsigned int width, height;
	struct
	{
		char up, down, left, right ,use;
	}controls;
};

extern MDPRGame *MDPR;

#endif // #ifndef MDPRGame_hpp
