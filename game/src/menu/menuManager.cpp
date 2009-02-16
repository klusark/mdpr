#include <boost/shared_ptr.hpp>
#include "menuManager.hpp"
#include "menuMain.hpp"

boost::shared_ptr<menuManager> menu;

menuManager::menuManager() : active(false)
{
	boost::shared_ptr<menuGeneric> mainMenu(new menuMain);
	menus["menuMain"] = mainMenu;

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
