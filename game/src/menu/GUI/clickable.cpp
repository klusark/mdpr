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
		std::cout<<"asfsdfsdfghhhhhh";
		if (widgetRect.Contains(xLocationAtClick, yLocationAtClick)){
			clicked = this;
			std::cout<<"asdf";
			rectClicked = true;
		}

		
	}

	void clickable::mouseDown()
	{
		std::cout<<"here?";
		xLocationAtClick = input.GetMouseX();
 		yLocationAtClick = input.GetMouseY();
		std::cout<<"asdfASDFsdaf";

	}

	void clickable::mouseUp()
	{
		std::cout<<"over here over?";
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
