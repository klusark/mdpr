#include <SFML/Graphics/Rect.hpp>
#include <boost/signal.hpp>
#include <iostream>

#include "../../MDPRGame.hpp"
#include "clickable.hpp"

namespace GUI
{
	const sf::Input& clickable::input = MDPR.App.GetInput();
	int clickable::xLocationAtClick, clickable::yLocationAtClick;
	clickable *clickable::clicked;
	bool clickable::rectClicked = false;
	clickable::clickable(sf::IntRect &rect)
		:	widgetRect(rect)
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
		xLocationAtClick = input.GetMouseX();
		yLocationAtClick = input.GetMouseY();

	}

	void clickable::mouseUp()
	{
		if (rectClicked){
			if (clicked->widgetRect.Contains(input.GetMouseX(), input.GetMouseY())){
				//clicked->onClick();
				std::cout<<"Clicked"<<std::endl;
			}
			clicked = 0;
			rectClicked = false;
		}
		
	}

}
