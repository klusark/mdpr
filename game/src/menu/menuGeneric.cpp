#pragma warning(push, 3)
#include <ClanLib/gui.h>
#pragma warning(pop)

#include "menuGeneric.hpp"
#include "menuManager.hpp"

menuGeneric::menuGeneric(CL_StyleManager &style, std::string const &resourceLocation)
	:	CL_GUIManager(&style)
{
	boost::shared_ptr<CL_ComponentManager> tmpcomponentManager(new CL_ComponentManager(resourceLocation, this));
	componentManager = tmpcomponentManager;
}


menuGeneric::~menuGeneric()
{
}

void menuGeneric::show()
{

	CL_GUIManager::show();
}
