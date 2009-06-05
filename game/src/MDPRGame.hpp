#ifndef MDPRGame_hpp
#define MDPRGame_hpp
#include "network/networkClient.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <boost/thread.hpp>

//!The main class for the game
/*!
Sets up and runs the game.
*/
class MDPRGame
{
public:
	//!Constructor
	/*!
	\param App The render window for the game to use.
	*/
	MDPRGame(sf::RenderWindow &App);
	
	//!Deconstructor
	~MDPRGame();
	
	//!Contains the event loop, and it starts the threads for drawing and updating. 
	void run();
	
	//!Quits the game
	static void quitGame();
	
	//!Draws the game
	void drawThread();
	
	//!updates the sprites
	void updateThread();
	
	//!the render window collected though the constructor
	sf::RenderWindow &App;
	
	//!The name of the player
	std::string playerName;
	
	//!The ip of the server to connect to
	std::string serverIP;
	
	//!The port to connect to
	std::string serverPort;
	static bool quit;
	sf::Clock Clock;
	networkClient *myNetworkClient;
	bool isRunning, userInterface;
	unsigned int width, height;
	struct
	{
		char up, down, left, right ,use;
	}controls;
private:

};

extern boost::shared_ptr<MDPRGame> MDPR;

#endif // #ifndef MDPRGame_hpp
