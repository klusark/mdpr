#ifndef powerup_hpp
#define powerup_hpp

#include "genericSprite.hpp"

class PowerUp : public GenericSprite
{
public:
	PowerUp(const std::string &name);
	~PowerUp();

	static GenericSprite::collidesWithContainer colidesWith;
	virtual collidesWithContainer getCollidesWith(void) const {return colidesWith;};

};

#endif // ifndef powerup_hpp
