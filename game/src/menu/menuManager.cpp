#include <ClanLib/core.h>
#pragma warning(push, 3)
#include <ClanLib/gui.h>
#include <ClanLib/guistylesilver.h>
#pragma warning(pop)

#include "menuManager.hpp"
#include "menuMain.hpp"
#include "menuOptions.hpp"
#include "menuProfile.hpp"

menuManager::menuManager(CL_ResourceManager resources) : active(false)
{
	
	CL_StyleManager_Silver style(&resources);
	//CL_GUIManager test(&style_manager);
	//CL_ComponentManager *comp_manager = new CL_ComponentManager("data/mdpr/gui/menuMain.xml", &test);
	menus["menuMain"] =		new menuMain(this, style, "data/mdpr/gui/menuMain.xml");
	menus["menuOptions"] =	new menuOptions(this, style, "data/mdpr/gui/menuOptions.xml");
	menus["menuProfile"] =	new menuProfile(this, style, "data/mdpr/gui/menuProfile.xml");
	currentMenu = menus["menuMain"];

}

menuManager::~menuManager()
{
	for(menuContainer::iterator it = menus.begin(); it != menus.end(); ++it){
		delete it->second;
	}
}

void menuManager::update()
{
	currentMenu->show();
}

void menuManager::changeCurrentMenu(std::string const &menuName)
{
	menuContainer::iterator iterator = menus.find(menuName);
	if (iterator != menus.end()){

		currentMenu->disable_input();
		currentMenu = iterator->second;
		currentMenu->enable_input();
#ifdef _DEBUG
		std::cout << "menuManager::changeCurrentMenu to \"" << menuName << "\" success\n";
#endif 
	}
#ifdef _DEBUG
	else
		std::cout << "menuManager::changeCurrentMenu to \"" << menuName << "\" failed\n";
#endif
	
}

bool menuManager::isActive()
{
	return active;
}

void menuManager::setActive(bool toggle)
{
	active = toggle;
}