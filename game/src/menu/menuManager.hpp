#ifndef menuManager_hpp
#define menuManager_hpp


#include <map>
#include "menuGeneric.hpp"

class menuGeneric;

class menuManager
{
public:
	menuManager(CL_ResourceManager resources);
	~menuManager();
	void update();
	void changeCurrentMenu(std::string const &menuName);
	bool isActive();
	void setActive(bool toggle);
private:
	typedef std::map<std::string, menuGeneric *> menuContainer;
	menuContainer menus;
	menuGeneric *currentMenu;
	bool active;
};

#endif
