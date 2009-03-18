#ifndef button_hpp
#define button_hpp

#include "clickable.hpp"
#include "widget.hpp"

namespace GUI
{
	class button : public widget, public clickable
	{
	public:
		button(sf::IntRect rect);
		~button();
	protected:
		void update();

	};
}

#endif //ifndef button_hpp
