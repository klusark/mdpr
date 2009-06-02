#include "menuGeneric.hpp"
#include "menuManager.hpp"
#include "../MDPRGame.hpp"

menuGeneric::menuGeneric(sf::RenderWindow &App)
	:	graphics(App)
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
