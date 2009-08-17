#ifndef powerup_hpp
#define powerup_hpp

#include "genericSprite.hpp"

class PowerUp : public GenericSprite
{
public:
	PowerUp(const std::string &name);
	~PowerUp();

	collidesWithContainer getCollidesWith(); //const {return colidesWith;};

};

#endif // ifndef powerup_hpp
