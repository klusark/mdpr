#ifndef chute_hpp
#define chute_hpp

#include "genericPowerUp.hpp"

class Chute : public genericPowerUp
{
public:
	Chute(GenericSprite *owner);
	~Chute();	
	void onActionKey();
	void update();

};

#endif // #ifndef chute_hpp
