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
		sf::IntRect &widgetRect;
		const sf::Input& input;

		static void mouseDown();

		static void mouseUp();

		static int xLocationAtClick, yLocationAtClick;
		static bool rectClicked;


		static clickable *clicked;


	};
}


#endif //ifndef clickable_hpp
