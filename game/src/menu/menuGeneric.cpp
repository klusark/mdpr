#pragma warning(push, 3)
#include <ClanLib/gui.h>
#pragma warning(pop)

#include "menuGeneric.hpp"
#include "menuManager.hpp"

menuGeneric::menuGeneric(menuManager *menu, CL_StyleManager &style, std::string const &resourceLocation)
	:	CL_GUIManager(&style),
		menu(menu)
{
	componentManager = new CL_ComponentManager(resourceLocation, this);
}


menuGeneric::~menuGeneric()
{
}

void menuGeneric::show()
{

	CL_GUIManager::show();
}