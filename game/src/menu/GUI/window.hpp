#ifndef window_hpp
#define window_hpp

#include "widget.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

namespace GUI
{
	class window : public widget
	{
	public:
		window(unsigned int width, unsigned int height, float x, float y, sf::Color color = sf::Color(118, 118, 118, 255));
		~window();

		typedef std::vector<boost::shared_ptr<widget> > widgetContainter;
		widgetContainter widgets;
		unsigned short width, height;

	};
}


#endif // ifndef window_hpp
