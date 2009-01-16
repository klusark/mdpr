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
		sf::Color color(0,255,0, 255);
		float radius = 25.0f;
		
		//rect.AddPoint(0, 	height-radius,  	color);
		makeCurve(radius, height-radius, color, -10, 0, false);
		//rect.AddPoint(radius, 	height,  	color);

		//rect.AddPoint(width-radius, 	height,  	color);
		makeCurve(width-radius, height-radius, color, 0, 10, false);
		//rect.AddPoint(width, 	height-radius,  	color);
		
		//rect.AddPoint(width, 	radius,  		color);
		makeCurve(width - radius, radius, color, -10, 0, true);
		//rect.AddPoint(width-radius, 	0,  		color);

		//rect.AddPoint(radius, 		0,  		color);
		makeCurve(radius, radius, color, 0, 10, true);
		//rect.AddPoint(0, 		radius,  		color);

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

	void window::makeCurve(float x, float y, sf::Color color, int startValue, int endValue, bool negitive)
	{

		// Create the points set
		sf::Vector2f Center(x, y);
		for (; startValue <= endValue; ++startValue)
		{
			//float Angle =  230+( i * 2 * 3.141592654f / (NbSegments*4));
			float num = float(startValue)/10.0f;
			float y = sqrt(float(1-num*num));
			if (negitive){
				y*=-1.0f;
				num*=-1.0f;
			}
			sf::Vector2f Offset(num, y);

			rect.AddPoint(Center + Offset * 25.0f, color);
		}

	}

}
