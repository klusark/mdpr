#ifndef clickable_hpp
#define clickable_hpp

#include <SFML/Window/Input.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <boost/signal.hpp>

namespace GUI
{
	class clickable
	{
	public:
		clickable(sf::IntRect &rect);
		~clickable();
		void update();
		boost::signal<void ()> onClick;

		static void clickable::mouseDown();

		static void clickable::mouseUp();

		static int xLocationAtClick, yLocationAtClick;
		static bool rectClicked;

		static const sf::Input& input;
		static clickable *clicked;
		sf::IntRect &widgetRect;

	};
}


#endif //ifndef clickable_hpp
