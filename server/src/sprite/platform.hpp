#ifndef platform_hpp
#define platform_hpp

#include "genericSprite.hpp"

class Platform : public genericSprite
{
public:
	Platform(const std::string &name);
	~Platform();
};

#endif // #ifndef platform_hpp
