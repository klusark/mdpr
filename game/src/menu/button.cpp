#include "button.hpp"

Button::Button()
{
}

Button::~Button()
{
}

void Button::keyPressed(gcn::KeyEvent &keyEvent)
{
	gcn::Button::keyPressed(keyEvent);
	onKeyPressed();
}

void Button::keyReleased(gcn::KeyEvent &keyEvent)
{
	gcn::Button::keyReleased(keyEvent);
	onKeyReleased();
}

void Button::mouseDragged(gcn::MouseEvent &mouseEvent)
{
	gcn::Button::mouseDragged(mouseEvent);
	onMouseDragged();
}

void Button::mouseEntered(gcn::MouseEvent &mouseEvent)
{
	gcn::Button::mouseEntered(mouseEvent);
	onMouseEntered();
}

void Button::mouseExited(gcn::MouseEvent &mouseEvent)
{
	gcn::Button::mouseExited(mouseEvent);
	onMouseExited();
}

void Button::mousePressed(gcn::MouseEvent &mouseEvent)
{
	gcn::Button::mousePressed(mouseEvent);
	onMousePressed();
}

void Button::mouseReleased(gcn::MouseEvent &mouseEvent)
{
	gcn::Button::mouseReleased(mouseEvent);
	onMouseReleased();
}
