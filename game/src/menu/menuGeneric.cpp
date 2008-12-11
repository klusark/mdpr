#pragma warning(push, 3)
#include <ClanLib/gui.h>
#pragma warning(pop)
#include "menuGeneric.hpp"

menuGeneric::menuGeneric(CL_StyleManager &style, std::string const &resourceLocation) : CL_GUIManager(&style)
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