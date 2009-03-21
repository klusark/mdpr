#ifndef input_hpp
#define input_hpp

#include <vector>
#include <SFML\Graphics.hpp>
#include <boost\signal.hpp>

namespace GUI
{
	class input
	{
	public:
		input();
		~input();

		void update();

		static void keyDown(sf::Key::Code key);

		static boost::signal<void (sf::Key::Code)> onKeyDown;

	};
}
#endif //ifndef input_hpp
