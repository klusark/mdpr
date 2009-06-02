#include "button.hpp"

Button::Button()
{
}

Button::~Button()
{
}

void 	Button::keyPressed (gcn::KeyEvent &keyEvent)
{
	onKeyPressed();
}

void 	Button::keyReleased (gcn::KeyEvent &keyEvent)
{
	onKeyReleased();
}

void 	Button::mouseDragged (gcn::MouseEvent &mouseEvent)
{
	onMouseDragged();
}

void 	Button::mouseEntered (gcn::MouseEvent &mouseEvent)
{
	onMouseEntered();
}

void 	Button::mouseExited (gcn::MouseEvent &mouseEvent)
{
	onMouseExited();
}

void 	Button::mousePressed (gcn::MouseEvent &mouseEvent)
{
	onMousePressed();
}

void 	Button::mouseReleased (gcn::MouseEvent &mouseEvent)
{
	onMouseReleased();
}
