#pragma warning(push, 3)
#include <ClanLib/gui.h>
#pragma warning(pop)

#include "menuProfile.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"


menuProfile::menuProfile(CL_StyleManager &style, std::string const &resourceLocation)
	:	menuGeneric(style, resourceLocation)
{
	CL_ListBox *levels = dynamic_cast<CL_ListBox*>(componentManager->get_component("profilesList"));
	levels->insert_item("asfd");
	levels->insert_item("asfdasf");
}

menuProfile::~menuProfile()
{
}
