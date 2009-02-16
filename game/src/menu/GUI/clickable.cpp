#include <SFML/Graphics/Rect.hpp>
#include <boost/signal.hpp>

#include "../../MDPRGame.hpp"
#include "clickable.hpp"

namespace GUI
{
	int clickable::xLocationAtClick, clickable::yLocationAtClick;
	clickable *clickable::clicked;
	bool clickable::rectClicked = false;
	clickable::clickable(sf::IntRect &rect)
		:	widgetRect(rect),
			input(MDPR->App.GetInput())
	{

	}

	clickable::~clickable()
	{
	}

	void clickable::update()
	{
		if (widgetRect.Contains(xLocationAtClick, yLocationAtClick)){
			clicked = this;
			rectClicked = true;
		}


	}

	void clickable::mouseDown()
	{
		xLocationAtClick = MDPR->App.GetInput().GetMouseX();
 		yLocationAtClick = MDPR->App.GetInput().GetMouseY();

	}

	void clickable::mouseUp()
	{
		if (rectClicked){
			if (clicked->widgetRect.Contains(MDPR->App.GetInput().GetMouseX(), MDPR->App.GetInput().GetMouseY())){
				clicked->onClick();
				//std::cout<<"Clicked"<<std::endl;

			}
			clicked = 0;
			rectClicked = false;
			xLocationAtClick = -1;
			xLocationAtClick = -1;
		}

	}

}
