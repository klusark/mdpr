#ifndef menuMain_hpp
#define menuMain_hpp

#include "menuGeneric.hpp"
#include "button.hpp"

class menuMain : public menuGeneric
{
public:
	menuMain(sf::RenderWindow &App);
	~menuMain();
	static void toThis();

	gcn::Label label;
	Button optionsButton;


};

#endif // ifndef menuMain_hpp
