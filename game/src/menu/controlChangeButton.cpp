#include "controlChangeButton.hpp"

ControlChangeButton::ControlChangeButton()
{
	setActionEventId("this");
	addActionListener(this);
}

ControlChangeButton::~ControlChangeButton()
{
}

void ControlChangeButton::keyPressed(gcn::KeyEvent &keyEvent)
{
	gcn::Button::keyPressed(keyEvent);

}

void ControlChangeButton::keyReleased(gcn::KeyEvent &keyEvent)
{
	gcn::Button::keyReleased(keyEvent);

}

void ControlChangeButton::action(const gcn::ActionEvent &actionEvent)
{
	if(actionEvent.getId() == "this"){
		setCaption("???");
	}
}