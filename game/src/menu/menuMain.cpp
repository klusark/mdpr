#include "menuMain.hpp"
#include "menuInGame.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"
#include "menuOptions.hpp"
#include "menuServerBrowser.hpp"
#include "menuControls.hpp"
#include "../helpers.hpp"
#include "../MDPRGame.hpp"

menuMain::menuMain(sf::RenderWindow &App)
	:	menuGeneric(App)
{
	label.setCaption("Marshmallow Duels");
	label.setDimension(gcn::Rectangle(100, 40, 200, 25));

	optionsButton.setCaption("Options");
	optionsButton.setDimension(gcn::Rectangle(100, 100, 0, 0));
	optionsButton.adjustSize();
	optionsButton.setActionEventId("options");
	optionsButton.addActionListener(this);

	controlsButton.setCaption("Controls");
	controlsButton.setDimension(gcn::Rectangle(100, 140, 0, 0));
	controlsButton.adjustSize();
	controlsButton.setActionEventId("controls");
	controlsButton.addActionListener(this);


	top.add(&label);
	top.add(&optionsButton);
	top.add(&controlsButton);
	
}

menuMain::~menuMain()
{
}

void menuMain::action(const gcn::ActionEvent &actionEvent)
{
	if(actionEvent.getId() == "options"){
		menuOptions::toThis();
	}else if(actionEvent.getId() == "controls"){
		menuControls::toThis();
	}

}

void menuMain::toThis()
{
	menu->changeCurrentMenu("menuMain");
}
