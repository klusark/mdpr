#ifndef menuOptions_hpp
#define menuOptions_hpp


#include "menuGeneric.hpp"

class menuOptions : public menuGeneric
{
public:
	menuOptions(menuManager *menu, CL_StyleManager &style, std::string const &resourceLocation);
	~menuOptions();
	//void onOptionsClicked();
	menuManager *menu;

};

#endif
