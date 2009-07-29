#ifndef menuManager_hpp
#define menuManager_hpp

#include <map>
#include "menuGeneric.hpp"
#include <Poco/SharedPtr.h>
#include <Poco/Mutex.h>
#include <string>
#include <CEGUI.h>
#include <openglrenderer.h>
#include "network/packets.hpp"

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
	void handleEvent(sf::Event& Event);

	//!Add a new server to the server list
	void addServer(fullServerEntry entry);

	void resize(float x, float y);

	Poco::Mutex menuMutex;
	sf::RenderWindow &App;

	typedef std::map<std::string, Poco::SharedPtr<MenuGeneric> > menuContainer;
	menuContainer menus;
	Poco::SharedPtr<MenuGeneric> currentMenu;
	bool active;

	CEGUI::System* MenuSystem;
	CEGUI::OpenGLRenderer* GUIRenderer;
	CEGUI::WindowManager* MenuWindowManager;
	const sf::Input* mInput;

	typedef std::map<sf::Key::Code, CEGUI::Key::Scan> KeyMap;
	typedef std::map<sf::Mouse::Button, CEGUI::MouseButton> MouseButtonMap;

	KeyMap mKeyMap;
	MouseButtonMap mMouseButtonMap;

	CEGUI::Key::Scan toCEGUIKey(sf::Key::Code Code);
	CEGUI::MouseButton toCEGUIMouseButton(sf::Mouse::Button Button);
	void initializeMaps();
	bool button(const CEGUI::EventArgs& e);
};

extern Poco::SharedPtr<MenuManager> menu;

#endif
