#include <ClanLib/core.h>
#pragma warning(push, 3)
#include <ClanLib/gui.h>
#include <ClanLib/guistylesilver.h>
#pragma warning(pop)
#include <boost/shared_ptr.hpp>

#include "menuManager.hpp"
#include "menuMain.hpp"
#include "menuOptions.hpp"
#include "menuProfile.hpp"

boost::shared_ptr<menuManager> menu;

menuManager::menuManager(CL_ResourceManager resources) : active(false)
{

	CL_StyleManager_Silver style(&resources);
	//CL_GUIManager test(&style_manager);
	//CL_ComponentManager *comp_manager = new CL_ComponentManager("data/mdpr/gui/menuMain.xml", &test);
	boost::shared_ptr<menuGeneric> mainMenu(new menuMain(style, "data/mdpr/gui/menuMain.xml"));
	menus["menuMain"] = mainMenu;

	boost::shared_ptr<menuGeneric> optionsMenu(new menuOptions(style, "data/mdpr/gui/menuOptions.xml"));
	menus["menuOptions"] = optionsMenu;

	boost::shared_ptr<menuGeneric> profileMenu(new menuProfile(style, "data/mdpr/gui/menuProfile.xml"));
	menus["menuProfile"] = profileMenu;
	currentMenu = menus["menuMain"];

}

menuManager::~menuManager()
{
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
