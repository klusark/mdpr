#include <boost/shared_ptr.hpp>
#include "menuManager.hpp"
#include "menuMain.hpp"
#include "menuOptions.hpp"
#include "menuInGame.hpp"
#include <iostream>

boost::shared_ptr<menuManager> menu;

menuManager::menuManager() : active(false)
{
	boost::shared_ptr<menuGeneric> mainMenu(new menuMain);
	menus["menuMain"] = mainMenu;

	boost::shared_ptr<menuGeneric> optionsMenu(new menuOptions);
	menus["menuOptions"] = optionsMenu;

	boost::shared_ptr<menuGeneric> inGameMenu(new menuInGame);
	menus["menuInGame"] = inGameMenu;

	changeCurrentMenu("menuMain");
}

menuManager::~menuManager()
{
}

void menuManager::update()
{
	currentMenu->update();
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
