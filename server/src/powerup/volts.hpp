#ifndef volts_hpp
#define volts_hpp

#include "genericPowerUp.hpp"

class Volts : public genericPowerUp
{
public:
	Volts(genericSprite *owner);
	~Volts();	
	void onActionKey();
	void update();

};

#endif // #ifndef volts_hpp
