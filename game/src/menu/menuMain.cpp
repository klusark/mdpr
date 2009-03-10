#include "menuMain.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"
#include "menuOptions.hpp"
#include "GUI/window.hpp"
#include "GUI/button.hpp"
#include "GUI/text.hpp"
#include "../MDPRGame.hpp"


menuMain::menuMain()
	:	menuGeneric()
{
	boost::shared_ptr<GUI::widget> window(new GUI::window(sf::IntRect(50, 50, 300, 540)));
	addWidget(window);

	boost::shared_ptr<GUI::widget> quitButton(new GUI::button(60, 20, 100, 300));
	dynamic_cast<GUI::button *>(quitButton.get())->onClick.connect(&MDPRGame::quitGame);
	addWidget(quitButton);

	boost::shared_ptr<GUI::widget> quitText(new GUI::text(50, 15, 105, 300, "Quit"));
	addWidget(quitText);

	boost::shared_ptr<GUI::widget> optionsButton(new GUI::button(60, 20, 100, 100));
	dynamic_cast<GUI::button *>(optionsButton.get())->onClick.connect(&menuOptions::toThis);
	addWidget(optionsButton);

	boost::shared_ptr<GUI::widget> optionsText(new GUI::text(50, 15, 105, 100, "Options"));
	addWidget(optionsText);
}

menuMain::~menuMain()
{
}

void menuMain::toThis()
{
	menu->changeCurrentMenu("menuMain");
}