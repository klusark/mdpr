#include "event.hpp"
#include <deque>
namespace engine
{
	namespace event
	{
		void createEvent(std::string name)
		{
			eventInfo currentEvent;
			currentEvent.name = name;
			events.push_front(currentEvent);

		}

	}
}