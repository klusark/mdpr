#pragma warning(push, 3)
#include <ClanLib/gui.h>
#pragma warning(pop)

#include "../MDPRApplication.hpp"
#include "menuMain.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"


menuMain::menuMain(menuManager *menu, CL_StyleManager &style, std::string const &resourceLocation)
	:	menuGeneric(menu, style, resourceLocation)
{
	CL_Button *quitButton = dynamic_cast<CL_Button*>(componentManager->get_component(("quitButton")));
	if (quitButton)
		slots.connect(quitButton->sig_clicked(), &Application, &MDPRApplication::onWindowClose);

	CL_Button *optionsButton = dynamic_cast<CL_Button*>(componentManager->get_component(("optionsButton")));
	if (optionsButton)
		slots.connect(optionsButton->sig_clicked(), this, &menuMain::onOptionsClicked);

}

menuMain::~menuMain()
{
}

void menuMain::onOptionsClicked()
{
	menu->changeCurrentMenu("menuOptions");
}