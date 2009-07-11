#ifndef menuControls_hpp
#define menuControls_hpp

#include "menuGeneric.hpp"
#include "controlChangeButton.hpp"

class menuControls : public MenuGeneric
{
public:
	menuControls(sf::RenderWindow &App);
	~menuControls();
	static void toThis();
	void action(const gcn::ActionEvent &actionEvent);

	gcn::Label labelUpKey;
	gcn::Label labelDownKey;
	gcn::Label labelRightKey;
	gcn::Label labelLeftKey;
	gcn::Label labelUseKey;

	ControlChangeButton upButton;
	ControlChangeButton downButton;
	ControlChangeButton leftButton;
	ControlChangeButton rightButton;
	ControlChangeButton useButton;

	gcn::Button saveButton;


};

#endif // ifndef menuControls_hpp
