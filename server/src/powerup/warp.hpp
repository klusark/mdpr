#ifndef warp_hpp
#define warp_hpp

#include "genericPowerUp.hpp"

class Warp : public genericPowerUp
{
public:
	Warp(GenericSprite *owner);
	~Warp();	
	void onActionKey();
	void update();

};

#endif // #ifndef mine_hpp
