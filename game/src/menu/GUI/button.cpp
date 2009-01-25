#include "button.hpp"

namespace GUI
{
	button::button()
		:	widget(),
			clickable(rect)
			
	{
		float x = 100.0f;
		float y = 100.0f;
		int width = 100;
		int height = 100;
		shape.SetX(x);
		shape.SetY(y);
		rect.Bottom = (int)y + height;
		rect.Top = (int)y;
		rect.Right = (int)x + width;
		rect.Left = (int)x;
		sf::Color color(0,255,255, 100);
		float radius = 25.0f;

		makeCurve(0,		height, radius, color, bottomLeft);

		makeCurve(width,	height, radius, color, bottomRight);

		makeCurve(width,	0,		radius, color, topRight);

		makeCurve(0,		0,		radius, color, topLeft);

	}

	button::~button()
	{
	}

	void button::update()
	{
		clickable::update();
	}

}
