#ifndef gun_hpp
#define gun_hpp

#include <SFML/System/Clock.hpp>

#include "genericPowerUp.hpp"

class Gun : public genericPowerUp
{
public:
	Gun(genericSprite *owner);
	~Gun();	
	void onActionKey();
	void update();
	sf::Clock clock;
	bool justShot;
	boost::shared_ptr<genericSprite> myDeathArea;
};

#endif // #ifndef gun_hpp
