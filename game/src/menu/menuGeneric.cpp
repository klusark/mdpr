#include "menuGeneric.hpp"
#include "menuManager.hpp"

MenuGeneric::MenuGeneric(sf::RenderWindow &App)
	:	graphics(App),
		ActionListener()
{
	setGraphics(&graphics);
	setInput(&input);
	setTop(&top);
	top.setDimension(gcn::Rectangle(0, 0, App.GetWidth(), App.GetHeight()));
	top.setOpaque(true);
}

MenuGeneric::~MenuGeneric()
{
}

void MenuGeneric::onChange()
{
}

void MenuGeneric::action(const gcn::ActionEvent &actionEvent)
{
}

void MenuGeneric::logic()
{
	gcn::Gui::logic();
}