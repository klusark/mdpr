/*#ifndef menuManager_hpp
#define menuManager_hpp

#include <map>
#include "menuGeneric.hpp"
#include <boost/shared_ptr.hpp>

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
	typedef std::map<std::string, boost::shared_ptr<menuGeneric> > menuContainer;
	menuContainer menus;
	boost::shared_ptr<menuGeneric> currentMenu;
	bool active;
};
extern boost::shared_ptr<menuManager> menu;
#endif
*/