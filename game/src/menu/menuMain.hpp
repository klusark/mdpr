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
	void action(const gcn::ActionEvent &actionEvent);

	gcn::Label label;
	gcn::Button optionsButton;
	gcn::Button controlsButton;


};

#endif // ifndef menuMain_hpp
