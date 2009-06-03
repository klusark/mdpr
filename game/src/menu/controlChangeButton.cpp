#include "controlChangeButton.hpp"

ControlChangeButton::ControlChangeButton(char *key)
	:	myKey(key),
		getKey(false)
{
	setActionEventId("this");
	addActionListener(this);
	std::string str(1, *key);
	setCaption(str);
}

ControlChangeButton::~ControlChangeButton()
{
}

void ControlChangeButton::keyPressed(gcn::KeyEvent &keyEvent)
{
	//gcn::Button::keyPressed(keyEvent);
	if (getKey){
		if(keyEvent.getKey().isCharacter()){
			*myKey = keyEvent.getKey().getValue();
		}
		std::string str(1, *myKey);
		setCaption(str);
		getKey = false;
	}
}

void ControlChangeButton::focusLost(const gcn::Event &event)
{
	gcn::Button::focusLost(event);
	std::string str(1, *myKey);
	setCaption(str);
	getKey = false;
}

void ControlChangeButton::action(const gcn::ActionEvent &actionEvent)
{
	if(actionEvent.getId() == "this"){
		setCaption("???");
		getKey = true;
	}
}