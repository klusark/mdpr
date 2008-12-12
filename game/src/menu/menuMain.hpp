#ifndef menuMain_hpp
#define menuMain_hpp


#include "menuGeneric.hpp"

class menuMain : public menuGeneric
{
public:
	menuMain(menuManager *menu, CL_StyleManager &style, std::string const &resourceLocation);
	~menuMain();
	void onOptionsClicked();

};

#endif
