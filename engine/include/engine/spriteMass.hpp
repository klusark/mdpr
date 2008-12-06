#ifndef spritemass_hpp
#define spritemass_hpp
#include "spriteInterface.hpp"
#include "sprite.hpp"
namespace engine
{
	class  Mass : public spriteInterface
	{
	public:
		Mass();
		virtual ~Mass();
		void update();
		std::string getName();
	};
}
#endif
