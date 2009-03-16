#include <string>
#include "text.hpp"

namespace GUI
{
	text::text(unsigned int width, unsigned int height, float x, float y, std::string sting)
	{
		
		if (!font.LoadFromFile("data/mdpr/DejaVuSansMono.ttf", 120)){
			
		}
		boost::shared_ptr<sf::Drawable> newDrawable(new sf::String(sting, font, height));
		drawable = newDrawable;
		drawable->SetX(x);
		drawable->SetY(y);

	}

	text::~text()
	{
	}

	void text::update()
	{
	}

}
