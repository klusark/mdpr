#include "menuOptions.hpp"
#include "menuGeneric.hpp"
#include "menuMain.hpp"
#include "menuManager.hpp"
#include "GUI/window.hpp"
#include "GUI/button.hpp"
#include "GUI/text.hpp"
#include "GUI/textBox.hpp"
#include "../MDPRGame.hpp"


menuOptions::menuOptions()
	:	menuGeneric()
{
	boost::shared_ptr<GUI::widget> window(new GUI::window(540, 300, 50, 50));
	addWidget(window);

	boost::shared_ptr<GUI::widget> backButton(new GUI::button(60, 20, 200, 300));
	dynamic_cast<GUI::button *>(backButton.get())->onClick.connect(&menuMain::toThis);
	addWidget(backButton);

	boost::shared_ptr<GUI::widget> backText(new GUI::text(50, 15, 205, 300, "Back"));
	addWidget(backText);

	boost::shared_ptr<GUI::widget> box(new GUI::textBox);
	addWidget(box);
}

menuOptions::~menuOptions()
{
}

void menuOptions::toThis()
{
	menu->changeCurrentMenu("menuOptions");
}