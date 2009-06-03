#ifndef controlChangeButton_hpp
#define controlChangeButton_hpp

#include <boost/signal.hpp>
#include <guichan.hpp>

class ControlChangeButton : public gcn::Button, public gcn::ActionListener
{
public:
	ControlChangeButton();
	~ControlChangeButton();

	void keyPressed (gcn::KeyEvent &keyEvent);
	void keyReleased (gcn::KeyEvent &keyEvent);
	void action(const gcn::ActionEvent &actionEvent);

};

#endif // #ifndef controlChangeButton_hpp