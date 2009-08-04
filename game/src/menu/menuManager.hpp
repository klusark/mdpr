#ifndef menuManager_hpp
#define menuManager_hpp

#include <map>
//#include "menuGeneric.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <Poco/SharedPtr.h>
#include <Poco/Mutex.h>
#include <string>
#include <CEGUI.h>
//#include <SFMLRenderer.hpp>
#include "network/packets.hpp"
#include "profile/Profile.hpp"
#include <openglrenderer.h>

//class MenuGeneric;

class MenuManager
{
public:
	MenuManager(sf::RenderWindow &App);
	~MenuManager();

	//!check if the menu manager is active
	/*
	@return returns if the menu manager is active
	*/
	bool isActive();

	//!sets the menu active or inactive
	/*!
	@param toggle the state to set the menu manager to
	*/
	void setActive(bool toggle);

	//!draw the gui to the screen
	void draw();

	//!passes events from sfml to cegui
	/*!
	@param Event the event to pass
	*/
	void handleEvent(sf::Event& Event);

	//!Add a new server to the server list
	/*!
	@param entry the entry to be added
	*/
	void addServer(fullServerEntry entry);

	//!add a new profile to the profile list
	/*!
	@param profile the profile to be added
	*/
	void addProfile(Profile &profile);

	void resize(float x, float y);

	Poco::Mutex menuMutex;
	sf::RenderWindow &App;

//	typedef std::map<std::string, Poco::SharedPtr<MenuGeneric> > menuContainer;
//	menuContainer menus;
//	Poco::SharedPtr<MenuGeneric> currentMenu;
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
	bool ConnectButton(const CEGUI::EventArgs& e);
	bool SelectProfileButton(const CEGUI::EventArgs& e);
};

extern Poco::SharedPtr<MenuManager> menu;

#endif
