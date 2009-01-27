#ifndef MDPRGame_hpp
#define MDPRGame_hpp

#include <SFML/Graphics/RenderWindow.hpp>

class MDPRGame
{
public:
	MDPRGame(sf::RenderWindow &App);
	~MDPRGame();
	void run();
	static void quitGame();
	sf::RenderWindow &App;
	std::string playerName;
	std::string serverIP;
	std::string serverPort;

private:

	static bool quit;
	sf::Clock Clock;

};

extern MDPRGame MDPR;

#endif //MDPRGame_hpp
