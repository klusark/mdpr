#include "menuInGame.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"
#include "menuOptions.hpp"
#include "GUI/window.hpp"
#include "GUI/button.hpp"
#include "GUI/text.hpp"
#include "../sprite/spriteManager.hpp"
#include "../MDPRGame.hpp"


menuInGame::menuInGame()
	:	menuGeneric()
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