#ifndef spriteInterface_hpp
#define spriteInterface_hpp
#include <string>
namespace engine
{
	class spriteInterface
	{
	public :
		virtual ~spriteInterface();
		virtual void update(){};
		virtual std::string getName();

	};
}

#endif
