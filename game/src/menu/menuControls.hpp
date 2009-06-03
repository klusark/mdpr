#ifndef menuControls_hpp
#define menuControls_hpp

#include "menuGeneric.hpp"
#include "controlChangeButton.hpp"

class menuControls : public menuGeneric
{
public:
	menuControls(sf::RenderWindow &App);
	~menuControls();
	static void toThis();
	void action(const gcn::ActionEvent &actionEvent);

	gcn::Label labelUpKey;
	ControlChangeButton upButton;
	ControlChangeButton downButton;


};

#endif // ifndef menuControls_hpp
