#pragma warning(push, 3)
#include <ClanLib/gui.h>
#pragma warning(pop)

#include "menuOptions.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"
menuOptions::menuOptions(menuManager *menu, CL_StyleManager &style, std::string const &resourceLocation)
	:	menuGeneric(menu, style, resourceLocation)
{
}

menuOptions::~menuOptions()
{
}
