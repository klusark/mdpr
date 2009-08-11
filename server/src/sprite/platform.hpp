#ifndef platform_hpp
#define platform_hpp

#include "genericSprite.hpp"

class Platform : public GenericSprite
{
public:
	Platform(const std::string &name);
	~Platform();
	static GenericSprite::collidesWithContainer colidesWith;
	virtual GenericSprite::collidesWithContainer getCollidesWith() const {return colidesWith;};
};

#endif // #ifndef platform_hpp
