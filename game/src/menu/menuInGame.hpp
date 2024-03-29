#ifndef menuInGame_hpp
#define menuInGame_hpp

#include "menuGeneric.hpp"

class menuInGame : public MenuGeneric
{
public:
	menuInGame(sf::RenderWindow &App);
	~menuInGame();
	static void toThis();
	void onChange();
	void logic();

	gcn::Label connectingLabel;
	gcn::Label statusLabel;

};

#endif // ifndef menuInGame_hpp
