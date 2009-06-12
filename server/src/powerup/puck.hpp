#ifndef puck_hpp
#define puck_hpp

#include "genericPowerUp.hpp"

class Puck : public genericPowerUp
{
public:
	Puck(genericSprite *owner);
	~Puck();	
	void onActionKey();
	void update();

};

#endif // #ifndef puck_hpp
