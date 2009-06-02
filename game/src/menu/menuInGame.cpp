#include "menuInGame.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"
#include "menuOptions.hpp"
#include "../sprite/spriteManager.hpp"
#include "../MDPRGame.hpp"


menuInGame::menuInGame(sf::RenderWindow &App)
	:	menuGeneric(App)
{

}

menuInGame::~menuInGame()
{
}

void menuInGame::toThis()
{
	menu->changeCurrentMenu("menuInGame");
	MDPR->myNetworkClient->connect();
}

void menuInGame::onChange()
{
	sprite.setActive(true);
}