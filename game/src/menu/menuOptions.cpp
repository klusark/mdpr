#include "menuOptions.hpp"
#include "menuGeneric.hpp"
#include "menuMain.hpp"
#include "menuManager.hpp"
#include "GUI/window.hpp"
#include "GUI/button.hpp"
#include "GUI/text.hpp"
#include "GUI/textBox.hpp"
#include "../MDPRGame.hpp"
#include "../helpers.hpp"


menuOptions::menuOptions()
	:	menuGeneric()
{
	boost::shared_ptr<GUI::widget> window(new GUI::window(XYWHToLTRB(50, 50, 540, 300)));
	addWidget(window);

	boost::shared_ptr<GUI::widget> backButton(new GUI::button(XYWHToLTRB(200, 300, 60, 20)));
	dynamic_cast<GUI::button *>(backButton.get())->onClick.connect(&menuMain::toThis);
	addWidget(backButton);

	boost::shared_ptr<GUI::widget> backText(new GUI::text(50, 15, 205, 300, "Back"));
	addWidget(backText);

	boost::shared_ptr<GUI::widget> box(new GUI::textBox(XYWHToLTRB(100, 300, 60, 20)));
	addWidget(box);
}

menuOptions::~menuOptions()
{
}

void menuOptions::toThis()
{
	menu->changeCurrentMenu("menuOptions");
}