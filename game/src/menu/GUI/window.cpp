#include <SFML/Graphics.hpp>

#include "window.hpp"
#include "../../MDPRGame.hpp"

namespace GUI
{
	window::window(unsigned short width, unsigned short height, float x, float y)
		:	width(width),
			height(height)
	{
		//sf::Shape Rect = sf::Shape::Rectangle(x, y, x+width, x+height, sf::Color(0, 128, 128));
		rect.SetX(x);
		rect.SetY(y);
		sf::Color color(0,255,0);
		rect.AddPoint(0, 		0,  		color);
		rect.AddPoint(0, 		height,  	color);
		rect.AddPoint(width, 	height,  	color);
		rect.AddPoint(width, 	0,  		color);

	}

	window::~window()
	{
	}

	void window::addWidget(widget newWidget)
	{
		widgets.push_back(newWidget);
	}

	void window::draw()
	{
		MDPR.App.Draw(rect);
		for (int i = 0; i < widgets.size(); ++i){
			widgets[i].draw();
		}
	}

}
