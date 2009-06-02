#include "menuMain.hpp"
#include "menuInGame.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"
#include "menuOptions.hpp"
#include "menuServerBrowser.hpp"
#include "../helpers.hpp"
#include "../MDPRGame.hpp"



menuMain::menuMain(sf::RenderWindow &App)
	:	menuGeneric(App)
{
	label.setCaption("Confirm this action?");
	label.setDimension(gcn::Rectangle(100, 40, 200, 25));

	optionsButton.setCaption("Options");
	optionsButton.setDimension(gcn::Rectangle(50, 50, 0, 0));
	optionsButton.adjustSize();

	top.add(&label);
	top.add(&optionsButton);
	
}

menuMain::~menuMain()
{
}

void menuMain::toThis()
{
	menu->changeCurrentMenu("menuMain");
}