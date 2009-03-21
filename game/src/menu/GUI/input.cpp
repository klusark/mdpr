#include "input.hpp"

namespace GUI
{
	boost::signal<void (sf::Key::Code)> input::onKeyDown;

	input::input()
	{
	}

	input::~input()
	{
	}

	void input::update()
	{
	}

	void input::keyDown(sf::Key::Code key)
	{
		onKeyDown(key);
	}
}
