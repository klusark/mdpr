#include "menuGeneric.hpp"
#include "menuManager.hpp"

menuGeneric::menuGeneric()
{
}

menuGeneric::~menuGeneric()
{
}

void menuGeneric::update()
{
	for(unsigned int i = 0; i < widgets.size(); ++i){
		widgets[i]->update();
		widgets[i]->draw();
	}

}

void menuGeneric::addWidget(boost::shared_ptr<GUI::widget> newWidget)
{
	widgets.push_back(newWidget);

}
