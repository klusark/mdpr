#ifndef MDPRGame_hpp
#define MDPRGame_hpp

#include <SFML/Graphics/RenderWindow.hpp>

class MDPRGame
{
public:
	MDPRGame(sf::RenderWindow &App);
	~MDPRGame();
	void run();
	std::string playerName;
private:
	sf::RenderWindow &App;
	bool quit;
	sf::Clock Clock;
};

extern MDPRGame MDPR;

#endif //MDPRGame_hpp
