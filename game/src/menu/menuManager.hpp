#ifndef menuManager_hpp
#define menuManager_hpp

#include <map>
#include "menuGeneric.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
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
	boost::mutex menuMutex;
	sf::RenderWindow &App;
	gcn::SFMLFont font;

	typedef std::map<std::string, boost::shared_ptr<menuGeneric> > menuContainer;
	menuContainer menus;
	boost::shared_ptr<menuGeneric> currentMenu;
	bool active;
};

extern boost::shared_ptr<menuManager> menu;

#endif
