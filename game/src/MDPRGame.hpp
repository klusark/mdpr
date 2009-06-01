#ifndef MDPRGame_hpp
#define MDPRGame_hpp
#include "network/networkClient.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <boost/thread.hpp>

class MDPRGame
{
public:
	MDPRGame(sf::RenderWindow &App);
	~MDPRGame();
	void run();
	static void quitGame();
	void drawThread();
	void updateThread();
	sf::RenderWindow &App;
	std::string playerName;
	std::string serverIP;
	std::string serverPort;
	static bool quit;
	sf::Clock Clock;
	networkClient *myNetworkClient;
	bool isRunning, userInterface;
private:

};

extern boost::shared_ptr<MDPRGame> MDPR;

#endif // ifndef MDPRGame_hpp
