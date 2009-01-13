#ifndef menuManager_hpp
#define menuManager_hpp

#include <map>
#include "menuGeneric.hpp"
#include <boost/shared_ptr.hpp>
#include <CEGUI.h>
#include <openglrenderer.h>

class menuGeneric;

class menuManager
{
public:
	menuManager();
	~menuManager();
	void update();
	void changeCurrentMenu(std::string menuName);
	bool isActive();
	void setActive(bool toggle);
private:
	typedef std::map<std::string, boost::shared_ptr<menuGeneric> > menuContainer;
	menuContainer menus;
	boost::shared_ptr<menuGeneric> currentMenu;
	bool active;
	CEGUI::OpenGLRenderer* myRenderer;
};
extern menuManager menu;
#endif
