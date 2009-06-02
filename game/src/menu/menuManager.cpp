#include <boost/shared_ptr.hpp>
#include "menuManager.hpp"
#include "menuMain.hpp"
#include "menuOptions.hpp"
#include "menuInGame.hpp"
#include "menuServerBrowser.hpp"
#include <iostream>

boost::shared_ptr<menuManager> menu;

menuManager::menuManager(sf::RenderWindow &App)
	:	active(false),
		App(App),
		font("data/mdpr/marshmallowDuel.ttf", 20)
{
	gcn::Widget::setGlobalFont(&font);
	boost::shared_ptr<menuGeneric> mainMenu(new menuMain(App));
	menus["menuMain"] = mainMenu;

	boost::shared_ptr<menuGeneric> optionsMenu(new menuOptions(App));
	menus["menuOptions"] = optionsMenu;

	boost::shared_ptr<menuGeneric> inGameMenu(new menuInGame(App));
	menus["menuInGame"] = inGameMenu;

	boost::shared_ptr<menuGeneric> serverBrowserMenu(new menuServerBrowser(App));
	menus["menuServerBrowser"] = serverBrowserMenu;

	changeCurrentMenu("menuMain");
}

menuManager::~menuManager()
{
}

void menuManager::logic()
{
	currentMenu->logic();
}

void menuManager::draw()
{
	currentMenu->draw();
}

void menuManager::changeCurrentMenu(std::string menuName)
{
	menuContainer::iterator iterator = menus.find(menuName);
	if (iterator != menus.end()){
		currentMenu = iterator->second;
		currentMenu->onChange();
	}else{
		std::cout << "Could not find menu." << std::endl;
	}
}

bool menuManager::isActive()
{
	return active;
}

void menuManager::setActive(bool toggle)
{
	active = toggle;
}
