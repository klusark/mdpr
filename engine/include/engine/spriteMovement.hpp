#ifndef spritemovement_hpp
#define spritemovement_hpp
#include "spriteInterface.hpp"
#include "sprite.hpp"
namespace engine
{
	class  Movement : public spriteInterface
	{
	public:
		EngineLib Movement();
		virtual ~Movement();
		void update();
		std::string getName();
	};
}
#endif
