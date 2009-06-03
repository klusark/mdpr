#include "menuGeneric.hpp"
#include "menuManager.hpp"

menuGeneric::menuGeneric(sf::RenderWindow &App)
	:	graphics(App),
		ActionListener()
{
	setGraphics(&graphics);
	setInput(&input);
	setTop(&top);
	top.setDimension(gcn::Rectangle(0, 0, 640, 400));
	top.setOpaque(true);
}

menuGeneric::~menuGeneric()
{
}

void menuGeneric::onChange()
{
}

void menuGeneric::action(const gcn::ActionEvent &actionEvent)
{
}