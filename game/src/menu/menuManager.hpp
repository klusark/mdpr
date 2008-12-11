#ifndef menuManager_hpp
#define menuManager_hpp
#if _MSC_VER > 1000
#pragma once
#endif

#include <map>
#include "menuGeneric.hpp"

class menuManager
{
public:
	menuManager();
	~menuManager();
	void update();
	void changeCurrentMenu(std::string const &menuName);
	
private:
	typedef std::map<std::string, menuGeneric *> menuContainer;
	menuContainer menus;
	menuGeneric *currentMenu;
};

#endif
