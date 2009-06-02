#ifndef menuInGame_hpp
#define menuInGame_hpp

#include "menuGeneric.hpp"

class menuInGame : public menuGeneric
{
public:
	menuInGame(sf::RenderWindow &App);
	~menuInGame();
	static void toThis();
	void onChange();


};

#endif // ifndef menuInGame_hpp
