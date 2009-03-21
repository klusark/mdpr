#include "widget.hpp"
#include "../../MDPRGame.hpp"

namespace GUI
{
	widget::widget()
		:	rect(*(new sf::IntRect()))
	{

	}

	widget::~widget()
	{
	}

	void widget::draw()
	{
		MDPR->App.Draw(*drawable.get());

	}

	void widget::update()
	{
	}

	void widget::makeCurve(float x, float y, float radius, sf::Color color, curveLocation location)
	{
		int startValue, endValue;
		switch(location)
		{
		case topLeft: 
			startValue = 0;
			endValue = 10;
			x += radius;
			y += radius;
			break;
		case bottomRight:
			startValue = 0;
			endValue = 10;
			y -= radius;
			x -= radius;
			break;
		case topRight:
			startValue = -10;
			endValue = 0;
			x -= radius;
			y += radius;
			break;
		case bottomLeft:
			startValue = -10;
			endValue = 0;
			x += radius;
			y -= radius;
			break;
		}

		// Create the points set
		sf::Vector2f Center(x, y);
		for (; startValue <= endValue; ++startValue)
		{
			float num = float(startValue)/10.0f;
			float y = sqrt(float(1-num*num));
			if (location == topLeft || location == topRight){
				y*=-1.0f;
				num*=-1.0f;
			}
			sf::Vector2f Offset(num, y);

			dynamic_cast<sf::Shape *>(drawable.get())->AddPoint(Center + Offset * radius, color);
		}

	}

	void widget::curvedBox(sf::IntRect rect, float radius, sf::Color color)
	{
		sf::FloatRect frect(rect.Left, rect.Top, rect.Right, rect.Bottom);
		curvedBox(frect, radius, color);
	}

	void widget::curvedBox(sf::FloatRect rect, float radius, sf::Color color)
	{
		makeCurve(rect.Left,	rect.Bottom,radius, color, bottomLeft);

		makeCurve(rect.Right,	rect.Bottom,radius, color, bottomRight);

		makeCurve(rect.Right,	rect.Top,	radius, color, topRight);

		makeCurve(rect.Left,	rect.Top,	radius, color, topLeft);
	}

}
