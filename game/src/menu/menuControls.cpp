#include "menuControls.hpp"
#include "menuInGame.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"
#include "menuOptions.hpp"
#include "menuServerBrowser.hpp"
#include "menuMain.hpp"
#include "../helpers.hpp"
#include "../MDPRGame.hpp"

menuControls::menuControls(sf::RenderWindow &App)
	:	menuGeneric(App),
		upButton(&MDPR->controls.up),
		downButton(&MDPR->controls.down),
		rightButton(&MDPR->controls.right),
		leftButton(&MDPR->controls.left),
		useButton(&MDPR->controls.use)
{
	labelUpKey.setCaption("Jump/Climb");
	labelUpKey.setDimension(gcn::Rectangle(20, 50, 0, 0));
	labelUpKey.adjustSize();

	labelDownKey.setCaption("Crouch");
	labelDownKey.setDimension(gcn::Rectangle(20, 90, 0, 0));
	labelDownKey.adjustSize();
		
	labelLeftKey.setCaption("Left");
	labelLeftKey.setDimension(gcn::Rectangle(20, 130, 0, 0));
	labelLeftKey.adjustSize();

	labelRightKey.setCaption("Right");
	labelRightKey.setDimension(gcn::Rectangle(20, 170, 0, 0));
	labelRightKey.adjustSize();

	labelUseKey.setCaption("Use");
	labelUseKey.setDimension(gcn::Rectangle(20, 210, 0, 0));
	labelUseKey.adjustSize();

	upButton.setDimension(gcn::Rectangle(150, 50, 50, 20));

	downButton.setDimension(gcn::Rectangle(150, 90, 50, 20));

	leftButton.setDimension(gcn::Rectangle(150, 130, 50, 20));

	rightButton.setDimension(gcn::Rectangle(150, 170, 50, 20));

	useButton.setDimension(gcn::Rectangle(150, 210, 50, 20));


	saveButton.setCaption("Save");
	saveButton.setDimension(gcn::Rectangle(320, 320, 0, 0));
	saveButton.adjustSize();
	saveButton.setActionEventId("save");
	saveButton.addActionListener(this);

	top.add(&saveButton);

	top.add(&labelUpKey);
	top.add(&labelDownKey);
	top.add(&labelRightKey);
	top.add(&labelLeftKey);
	top.add(&labelUseKey);

	top.add(&upButton);
	top.add(&downButton);
	top.add(&leftButton);
	top.add(&rightButton);
	top.add(&useButton);
	
}

menuControls::~menuControls()
{
}

void menuControls::action(const gcn::ActionEvent &actionEvent)
{
	if(actionEvent.getId() == "save"){
		menuMain::toThis();
	}

}

void menuControls::toThis()
{
	menu->changeCurrentMenu("menuControls");
}
