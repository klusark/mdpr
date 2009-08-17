#ifndef platform_hpp
#define platform_hpp

#include "genericSprite.hpp"

class Platform : public GenericSprite
{
public:
	Platform(const std::string &name);
	~Platform();

	GenericSprite::collidesWithContainer getCollidesWith();
};

#endif // #ifndef platform_hpp
