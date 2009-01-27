#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

#include "window.hpp"
#include "button.hpp"
#include "../../MDPRGame.hpp"
#include <iostream>

namespace GUI
{
	window::window(unsigned short width, unsigned short height, float x, float y)
		:	width(width),
			height(height)
	{
		//sf::Shape Rect = sf::Shape::Rectangle(x, y, x+width, x+height, sf::Color(0, 128, 128));
		boost::shared_ptr<sf::Drawable> newDrawable(new sf::Shape);
		drawable = newDrawable;
		
		drawable->SetX(x);
		drawable->SetY(y);
		rect.Bottom = (int)y + height;
		rect.Top = (int)y;
		rect.Right = (int)x + width;
		rect.Left = (int)x;
		sf::Color color(0, 255, 0, 255);
		float radius = 25.0f;

		makeCurve(0,		height, radius, color, bottomLeft);

		makeCurve(width,	height, radius, color, bottomRight);

		makeCurve(width,	0,		radius, color, topRight);

		makeCurve(0,		0,		radius, color, topLeft);

	}

	window::~window()
	{
	}

	/*void window::addWidget(boost::shared_ptr<widget> newWidget)
	{
		widgets.push_back(newWidget);
	}*/

	/*void window::draw()
	{
		MDPR.App.Draw(drawable);
		for (unsigned int i = 0; i < widgets.size(); ++i){
			widgets[i]->draw();
		}
	}*/
}
