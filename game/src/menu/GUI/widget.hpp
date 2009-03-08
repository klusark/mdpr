#ifndef widget_hpp
#define widget_hpp

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

namespace GUI
{
	class widget
	{
	public:
		widget();
		~widget();
		virtual void draw();
		virtual void update();

	//protected:
		boost::shared_ptr<sf::Drawable> drawable;
		sf::IntRect rect;
		enum curveLocation
		{
			topRight,
			topLeft,
			bottomLeft,
			bottomRight,
		};
		void makeCurve(float x, float y, float radius, sf::Color color, curveLocation location);


	};
}


#endif //ifndef widget_hpp
