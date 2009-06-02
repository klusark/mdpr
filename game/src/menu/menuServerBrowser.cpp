#include "menuServerBrowser.hpp"
#include "menuGeneric.hpp"
#include "menuMain.hpp"
#include "menuManager.hpp"
#include "../MDPRGame.hpp"


menuServerBrowser::menuServerBrowser(sf::RenderWindow &App)
	:	menuGeneric(App)
{

}

menuServerBrowser::~menuServerBrowser()
{
}

void menuServerBrowser::toThis()
{
	menu->changeCurrentMenu("menuServerBrowser");
}