#ifndef MDPRGame_hpp
#define MDPRGame_hpp

class MDPRGame
{
public:
	MDPRGame(sf::RenderWindow &App);
	~MDPRGame();
	void run();
private:
	sf::RenderWindow &App;
	bool quit;
	sf::Clock Clock;
};

#endif //MDPRGame_hpp
