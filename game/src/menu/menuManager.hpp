#ifndef menuManager_hpp
#define menuManager_hpp

#include <map>
#include "menuGeneric.hpp"
#include <Poco/SharedPtr.h>
#include <Poco/Mutex.h>
#include <string>
#include <CEGUI.h>
#include <openglrenderer.h>

class MenuGeneric;

class MenuManager
{
public:
	MenuManager(sf::RenderWindow &App);
	~MenuManager();
	void logic();
	void changeCurrentMenu(std::string menuName);
	bool isActive();
	void setActive(bool toggle);
	void draw();
	Poco::Mutex menuMutex;
	sf::RenderWindow &App;
	gcn::SFMLFont font;

	typedef std::map<std::string, Poco::SharedPtr<MenuGeneric> > menuContainer;
	menuContainer menus;
	Poco::SharedPtr<MenuGeneric> currentMenu;
	bool active;

	CEGUI::System* mSystem;
	CEGUI::OpenGLRenderer* mRenderer;
	CEGUI::WindowManager* mWindowManager;
	const sf::Input* mInput;

	typedef std::map<sf::Key::Code, CEGUI::Key::Scan> KeyMap;
	typedef std::map<sf::Mouse::Button, CEGUI::MouseButton> MouseButtonMap;

	KeyMap mKeyMap;
	MouseButtonMap mMouseButtonMap;

	CEGUI::Key::Scan toCEGUIKey(sf::Key::Code Code);
	CEGUI::MouseButton toCEGUIMouseButton(sf::Mouse::Button Button);
	void initializeMaps();
};

extern Poco::SharedPtr<MenuManager> menu;

#endif
