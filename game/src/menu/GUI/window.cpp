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
		rect.SetX(x);
		rect.SetY(y);
		sf::Color color(0,255,0);
		rect.AddPoint(0, 		0,  		color);

		rect.AddPoint(0, 	height-25,  	color);
		//makeCurve(25, height-25, color);
		rect.AddPoint(25, 	height,  	color);

		rect.AddPoint(width-25, 	height,  	color);
		//makeCurve(width-25, height-25, color);
		rect.AddPoint(width, 	height-25,  	color);
		
		rect.AddPoint(width, 	25,  		color);
		makeCurve(width-25, 25, color);
		rect.AddPoint(width-25, 	0,  		color);

		//boost::shared_ptr<widget> test(new button());
		//addWidget(test);
		


	}

	window::~window()
	{
	}

	void window::addWidget(boost::shared_ptr<widget> newWidget)
	{
		widgets.push_back(newWidget);
	}

	void window::draw()
	{
		MDPR.App.Draw(rect);
		for (unsigned int i = 0; i < widgets.size(); ++i){
			widgets[i]->draw();
		}
	}

	void window::makeCurve(float x, float y, sf::Color color)
	{
		static const int NbSegments = 40;

		// Create the points set
		sf::Vector2f Center(x, y);
		for (int i = 0; i < NbSegments; ++i)
		{
			float Angle =  230+( i * 2 * 3.141592654f / (NbSegments*4));
			sf::Vector2f Offset(cos(Angle), sin(Angle));

			rect.AddPoint(Center + Offset * 25.0f, color);
		}

	}

}
