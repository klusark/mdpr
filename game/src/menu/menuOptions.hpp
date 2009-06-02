#ifndef menuOptions_hpp
#define menuOptions_hpp

#include "menuGeneric.hpp"

class menuOptions : public menuGeneric
{
public:
	menuOptions(sf::RenderWindow &App);
	~menuOptions();
	static void toThis();


};

#endif // ifndef menuOptions_hpp
