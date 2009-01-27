#include "menuMain.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"
#include "GUI/window.hpp"
#include "GUI/button.hpp"
#include "GUI/text.hpp"
#include "../MDPRGame.hpp"


menuMain::menuMain()
	:	menuGeneric()
{
	boost::shared_ptr<GUI::widget> window(new GUI::window(540,300,50,50));
	addWidget(window);

	boost::shared_ptr<GUI::widget> quit(new GUI::button);
	dynamic_cast<GUI::button *>(quit.get())->onClick.connect(&MDPRGame::quitGame);
	addWidget(quit);

	boost::shared_ptr<GUI::widget> text(new GUI::text);
	addWidget(text);
}

menuMain::~menuMain()
{
}
