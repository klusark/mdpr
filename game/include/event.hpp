#ifndef event_hpp
#define event_hpp
#include <string>
#include <deque>

namespace engine
{
	namespace event
	{
		struct eventInfo
		{
			std::string name;

		};
		enum eventTypes
		{
			keyDown,
		};
		std::deque<eventInfo> events;
		void createEvent(std::string name);

	}
}
#endif
