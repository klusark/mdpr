#ifndef MDPRGame_hpp
#define MDPRGame_hpp

class MDPRGame
{
public:
	MDPRGame(sf::RenderWindow &App);
	~MDPRGame();
	void run();
	void onWindowClose();
private:
	sf::RenderWindow &App;
	bool quit;
};

#endif //MDPRGame_hpp
