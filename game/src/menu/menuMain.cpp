#include "menuMain.hpp"
#include "menuGeneric.hpp"
#include "menuManager.hpp"
#include "GUI/window.hpp"
#include "GUI/button.hpp"
#include "../MDPRGame.hpp"


menuMain::menuMain()
	:	menuGeneric()
{
	boost::shared_ptr<GUI::widget> test(new GUI::window(540,300,50,50));
	addWidget(test);
	boost::shared_ptr<GUI::widget> quit(new GUI::button);
	//dynamic_cast<GUI::button *>(quit.get())->onClick.connect(&MDPRGame::quitGame);
	addWidget(quit);

}

menuMain::~menuMain()
{
}
