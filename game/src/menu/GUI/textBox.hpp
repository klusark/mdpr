#ifndef textBox_hpp
#define textBox_hpp

#include "widget.hpp"
#include "clickable.hpp"
#include "window.hpp"

namespace GUI
{
	class textBox : public widget, public clickable
	{
	public:
		textBox(sf::IntRect rect);
		~textBox();
		void mouseDown();
		void draw();
		void update();
		void clicked();
		window textArea;
		sf::IntRect &rect;
		boost::shared_ptr<sf::Drawable> text;
		sf::String *ptrToTextString;
		sf::Shape position;
		sf::Font font;
	};
}
#endif //ifndef textBox_hpp