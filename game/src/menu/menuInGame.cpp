#include "menuInGame.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"
#include "menuOptions.hpp"
#include "MDPRGame.hpp"


menuInGame::menuInGame(sf::RenderWindow &App)
	:	menuGeneric(App)
{
	top.setOpaque(true);

	connectingLabel.setCaption("Connecting");
	connectingLabel.setDimension(gcn::Rectangle(250, 10, 0, 0));
	connectingLabel.adjustSize();

	top.add(&connectingLabel);
	top.add(&statusLabel);

}

menuInGame::~menuInGame()
{
}

void menuInGame::logic()
{
	if(MDPR->myNetworkClient->currentState == connectedState){
		top.setOpaque(false);
	}
}

void menuInGame::toThis()
{
	menu->changeCurrentMenu("menuInGame");
	
}

void menuInGame::onChange()
{
	//sprite.setActive(true);
}