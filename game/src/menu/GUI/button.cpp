#include "button.hpp"

namespace GUI
{
	button::button(unsigned int width, unsigned int height, float x, float y)
		:	widget(),
			clickable(rect)
			
	{
		boost::shared_ptr<sf::Drawable> newDrawable(new sf::Shape);
		drawable = newDrawable;

		drawable->SetX(x);
		drawable->SetY(y);
		rect.Bottom = (int)y + height;
		rect.Top = (int)y;
		rect.Right = (int)x + width;
		rect.Left = (int)x;
		sf::Color color(255,128,0, 255);
		float radius = 5.0f;

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
