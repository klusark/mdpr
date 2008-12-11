#include <ClanLib/core.h>
#pragma warning(push, 3)
#include <ClanLib/gui.h>
#include <ClanLib/guistylesilver.h>
#pragma warning(pop)

#include "menuManager.hpp"

menuManager::menuManager()
{
	CL_ResourceManager resources("data/mdpr/gui/gui.xml", false);
	CL_StyleManager_Silver style(&resources);
	//CL_GUIManager test(&style_manager);
	//CL_ComponentManager *comp_manager = new CL_ComponentManager("data/mdpr/gui/menuMain.xml", &test);
	menus["menuMain"] = new menuGeneric(style, "data/mdpr/gui/menuMain.xml");
	changeCurrentMenu("menuMain");

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
	if (iterator == menus.end()){
		return;
	}
	currentMenu = menus[menuName];
}