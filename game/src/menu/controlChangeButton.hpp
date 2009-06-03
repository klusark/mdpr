#ifndef controlChangeButton_hpp
#define controlChangeButton_hpp

#include <boost/signal.hpp>
#include <guichan.hpp>

class ControlChangeButton : public gcn::Button, public gcn::ActionListener
{
public:
	ControlChangeButton(char *key);
	~ControlChangeButton();
	char *myKey;
	bool getKey;

	void keyPressed (gcn::KeyEvent &keyEvent);
	void action(const gcn::ActionEvent &actionEvent);
	void focusLost(const gcn::Event &event);

};

#endif // #ifndef controlChangeButton_hpp