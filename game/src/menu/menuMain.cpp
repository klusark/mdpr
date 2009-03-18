#include "menuMain.hpp"
#include "menuInGame.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"
#include "menuOptions.hpp"
#include "menuServerBrowser.hpp"
#include "GUI/window.hpp"
#include "GUI/button.hpp"
#include "GUI/text.hpp"
#include "../helpers.hpp"
#include "../MDPRGame.hpp"


menuMain::menuMain()
	:	menuGeneric()
{
	boost::shared_ptr<GUI::widget> window(new GUI::window(XYWHToLTRB(50, 50, 540, 300)));
	addWidget(window);

	boost::shared_ptr<GUI::widget> quitButton(new GUI::button(XYWHToLTRB(100, 300, 60, 20)));
	dynamic_cast<GUI::button *>(quitButton.get())->onClick.connect(&MDPRGame::quitGame);
	addWidget(quitButton);

	boost::shared_ptr<GUI::widget> inGameButton(new GUI::button(XYWHToLTRB(200, 200, 60, 20)));
	dynamic_cast<GUI::button *>(inGameButton.get())->onClick.connect(&menuInGame::toThis);
	addWidget(inGameButton);

	boost::shared_ptr<GUI::widget> menuServerBrowserButton(new GUI::button(XYWHToLTRB(300, 300, 60, 20)));
	dynamic_cast<GUI::button *>(menuServerBrowserButton.get())->onClick.connect(&menuServerBrowser::toThis);
	addWidget(menuServerBrowserButton);

	boost::shared_ptr<GUI::widget> quitText(new GUI::text(50, 15, 105, 300, "Quit"));
	addWidget(quitText);

	boost::shared_ptr<GUI::widget> optionsButton(new GUI::button(XYWHToLTRB(100, 100, 60, 20)));
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