#include "menuOptions.hpp"
#include "menuGeneric.hpp"
#include "menuMain.hpp"
#include "menuManager.hpp"
#include "../MDPRGame.hpp"
#include "../helpers.hpp"


menuOptions::menuOptions(sf::RenderWindow &App)
	:	menuGeneric(App)
{

}

menuOptions::~menuOptions()
{
}

void menuOptions::toThis()
{
	menu->changeCurrentMenu("menuOptions");
}