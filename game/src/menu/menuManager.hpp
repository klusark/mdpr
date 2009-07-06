#ifndef menuManager_hpp
#define menuManager_hpp

#include <map>
#include "menuGeneric.hpp"
#include <Poco/SharedPtr.h>
#include <Poco/Mutex.h>
#include <string>


class menuGeneric;

class menuManager
{
public:
	menuManager(sf::RenderWindow &App);
	~menuManager();
	void logic();
	void changeCurrentMenu(std::string menuName);
	bool isActive();
	void setActive(bool toggle);
	void draw();
	Poco::Mutex menuMutex;
	sf::RenderWindow &App;
	gcn::SFMLFont font;

	typedef std::map<std::string, Poco::SharedPtr<menuGeneric> > menuContainer;
	menuContainer menus;
	Poco::SharedPtr<menuGeneric> currentMenu;
	bool active;
};

extern Poco::SharedPtr<menuManager> menu;

#endif
