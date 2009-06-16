#include "menuOptions.hpp"
#include "menuGeneric.hpp"
#include "menuMain.hpp"
#include "menuManager.hpp"
#include "MDPRGame.hpp"
#include "helpers.hpp"

menuOptions::menuOptions(sf::RenderWindow &App)
	:	menuGeneric(App)
{
	char str[4];
	textResWidth.setDimension(gcn::Rectangle(100, 100, 50, 20));
	textResWidth.setAllowedCharacters("", false, true);
	textResWidth.setMaxCharacters(4);
	sprintf(str, "%d", MDPR->width);
	textResWidth.setText(str);
	
	textResHeight.setDimension(gcn::Rectangle(100, 150, 50, 20));
	textResHeight.setAllowedCharacters("", false, true);
	textResHeight.setMaxCharacters(4);
	sprintf(str, "%d", MDPR->height);
	textResHeight.setText(str);
	textResHeight.setActionEventId("test");
	textResHeight.addActionListener(this);

	labelResWidth.setCaption("Width");
	labelResWidth.setDimension(gcn::Rectangle(100, 80, 0, 0));
	labelResWidth.adjustSize();

	labelResHeight.setCaption("Height");
	labelResHeight.setDimension(gcn::Rectangle(100, 130, 0, 0));
	labelResHeight.adjustSize();

	labelVsync.setCaption("Vsync");
	labelVsync.setDimension(gcn::Rectangle(100, 200, 0, 0));
	labelVsync.adjustSize();

	labelFullScreen.setCaption("Full Screen");
	labelFullScreen.setDimension(gcn::Rectangle(100, 250, 0, 0));
	labelFullScreen.adjustSize();

	saveButton.setCaption("Save");
	saveButton.setDimension(gcn::Rectangle(320, 320, 0, 0));
	saveButton.adjustSize();
	saveButton.setActionEventId("save");
	saveButton.addActionListener(this);

	fullScreen.setDimension(gcn::Rectangle(200, 200, 20, 20));

	vsync.setDimension(gcn::Rectangle(200, 250, 20, 20));


	top.add(&textResWidth);
	top.add(&textResHeight);
	top.add(&labelResWidth);
	top.add(&labelResHeight);
	top.add(&saveButton);
	top.add(&fullScreen);
	top.add(&vsync);
	top.add(&labelVsync);
	top.add(&labelFullScreen);
}

menuOptions::~menuOptions()
{
}

void menuOptions::action(const gcn::ActionEvent &actionEvent)
{
	if(actionEvent.getId() == "save"){
		MDPR->App.UseVerticalSync(vsync.isSelected());
		
		menuMain::toThis();
	}
}

void menuOptions::toThis()
{
	menu->changeCurrentMenu("menuOptions");
}
