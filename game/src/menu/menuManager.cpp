#include <iostream>
#include <boost/shared_ptr.hpp>
#include <openglrenderer.h>
#include <CEGUI.h>
#include "menuManager.hpp"

menuManager menu;

menuManager::menuManager() : active(false)
{
	//myRenderer = new CEGUI::OpenGLRenderer(0 , 640, 400);
	/*CL_StyleManager_Silver style(&resources);
	//CL_GUIManager test(&style_manager);
	//CL_ComponentManager *comp_manager = new CL_ComponentManager("data/mdpr/gui/menuMain.xml", &test);
	boost::shared_ptr<menuGeneric> mainMenu(new menuMain(style, "data/mdpr/gui/menuMain.xml"));
	menus["menuMain"] = mainMenu;

	boost::shared_ptr<menuGeneric> optionsMenu(new menuOptions(style, "data/mdpr/gui/menuOptions.xml"));
	menus["menuOptions"] = optionsMenu;

	boost::shared_ptr<menuGeneric> profileMenu(new menuProfile(style, "data/mdpr/gui/menuProfile.xml"));
	menus["menuProfile"] = profileMenu;
	currentMenu = menus["menuMain"];*/

}

menuManager::~menuManager()
{
	//delete myRenderer;
}

void menuManager::update()
{
	//CEGUI::System::getSingleton().renderGUI();
	
}

void menuManager::changeCurrentMenu(std::string menuName)
{
	//menuContainer::iterator iterator = menus.find(menuName);
	//if (iterator != menus.end()){

		//currentMenu->disable_input();
		//currentMenu = iterator->second;
		//currentMenu->enable_input();
	//}
}

bool menuManager::isActive()
{
	return active;
}

void menuManager::setActive(bool toggle)
{
	active = toggle;
}
