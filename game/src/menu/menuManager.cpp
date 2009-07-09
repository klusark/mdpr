#include <Poco/SharedPtr.h>
#include <Poco/Util/Application.h>
#include "menuManager.hpp"
#include "menuMain.hpp"
#include "menuOptions.hpp"
#include "menuInGame.hpp"
#include "menuServerBrowser.hpp"
#include "menuControls.hpp"

Poco::SharedPtr<menuManager> menu;

menuManager::menuManager(sf::RenderWindow &App)
	:	active(false),
		App(App),
		font("data/mdpr/marshmallowDuel.ttf", 20)
{
	gcn::Widget::setGlobalFont(&font);
	Poco::SharedPtr<menuGeneric> mainMenu(new menuMain(App));
	menus["menuMain"] = mainMenu;

	Poco::SharedPtr<menuGeneric> optionsMenu(new menuOptions(App));
	menus["menuOptions"] = optionsMenu;

	Poco::SharedPtr<menuGeneric> inGameMenu(new menuInGame(App));
	menus["menuInGame"] = inGameMenu;

	Poco::SharedPtr<menuGeneric> serverBrowserMenu(new menuServerBrowser(App));
	menus["menuServerBrowser"] = serverBrowserMenu;

	Poco::SharedPtr<menuGeneric> controlsMenu(new menuControls(App));
	menus["menuControls"] = controlsMenu;

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
		Poco::Util::Application::instance().logger().warning("Could not find menu: " + menuName);
		//std::cout << "Could not find menu." << std::endl;
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
