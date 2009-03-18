#include "menuServerBrowser.hpp"
#include "menuGeneric.hpp"
#include "menuMain.hpp"
#include "menuManager.hpp"
#include "GUI/window.hpp"
#include "GUI/button.hpp"
#include "GUI/text.hpp"
#include "GUI/textBox.hpp"
#include "GUI/listBox.hpp"
#include "../MDPRGame.hpp"


menuServerBrowser::menuServerBrowser()
	:	menuGeneric()
{
	boost::shared_ptr<GUI::widget> window(new GUI::listBox);
	addWidget(window);

	boost::shared_ptr<GUI::widget> backButton(new GUI::button(sf::IntRect(60, 20, 200, 300)));
	dynamic_cast<GUI::button *>(backButton.get())->onClick.connect(&menuMain::toThis);
	addWidget(backButton);

	boost::shared_ptr<GUI::widget> backText(new GUI::text(50, 15, 205, 300, "Back"));
	addWidget(backText);

}

menuServerBrowser::~menuServerBrowser()
{
}

void menuServerBrowser::toThis()
{
	menu->changeCurrentMenu("menuServerBrowser");
}