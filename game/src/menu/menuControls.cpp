#include "menuControls.hpp"
#include "menuInGame.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"
#include "menuOptions.hpp"
#include "menuServerBrowser.hpp"
#include "../helpers.hpp"
#include "../MDPRGame.hpp"

menuControls::menuControls(sf::RenderWindow &App)
	:	menuGeneric(App),
		upButton(&MDPR->controls.up),
		downButton(&MDPR->controls.down)
{
	labelUpKey.setCaption("Jump/Climb");
	labelUpKey.setDimension(gcn::Rectangle(20, 50, 0, 0));
	labelUpKey.adjustSize();

	//upButton.setCaption("test");
	upButton.setDimension(gcn::Rectangle(150, 50, 50, 20));
	//upButton.adjustSize();

	downButton.setDimension(gcn::Rectangle(150, 90, 50, 20));

	top.add(&upButton);
	top.add(&downButton);
	top.add(&labelUpKey);
	
}

menuControls::~menuControls()
{
}

void menuControls::action(const gcn::ActionEvent &actionEvent)
{

}

void menuControls::toThis()
{
	menu->changeCurrentMenu("menuControls");
}
