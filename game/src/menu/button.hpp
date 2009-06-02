#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <boost/signal.hpp>
#include <guichan.hpp>

class Button : public gcn::Button
{
public:
	Button();
	~Button();

	void 	keyPressed (gcn::KeyEvent &keyEvent);
	void 	keyReleased (gcn::KeyEvent &keyEvent);
	void 	mouseDragged (gcn::MouseEvent &mouseEvent);
	void 	mouseEntered (gcn::MouseEvent &mouseEvent);
	void 	mouseExited (gcn::MouseEvent &mouseEvent);
	void 	mousePressed (gcn::MouseEvent &mouseEvent);
	void 	mouseReleased (gcn::MouseEvent &mouseEvent);

	boost::signal<void ()> onKeyPressed;
	 
	boost::signal<void ()> onKeyReleased;
	 	
	boost::signal<void ()> onMouseDragged;
	 	
	boost::signal<void ()> onMouseEntered;
	 	
	boost::signal<void ()> onMouseExited;

	boost::signal<void ()> onMousePressed;

	boost::signal<void ()> onMouseReleased;
};

#endif // #ifndef BUTTON_HPP