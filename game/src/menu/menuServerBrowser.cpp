#include "menuServerBrowser.hpp"
#include "menuGeneric.hpp"
#include "menuMain.hpp"
#include "menuManager.hpp"
#include "MDPRGame.hpp"


menuServerBrowser::menuServerBrowser(sf::RenderWindow &App)
	:	menuGeneric(App)
{

	serverListBox.setDimension(gcn::Rectangle(50, 50, 200, 200));
	serverListBox.setListModel(&serverListModel);
	top.add(&serverListBox);
}

menuServerBrowser::~menuServerBrowser()
{
}

void menuServerBrowser::toThis()
{
	menu->changeCurrentMenu("menuServerBrowser");
}