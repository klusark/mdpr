#ifndef gun_hpp
#define gun_hpp

#include <SFML/System/Clock.hpp>

#include "genericPowerUp.hpp"

class Gun : public genericPowerUp
{
public:
	Gun(GenericSprite *owner);
	~Gun();	
	void onActionKey();
	void update();
	sf::Clock clock;
	bool justShot;
	Poco::SharedPtr<GenericSprite> mySelectionArea;
};

#endif // #ifndef gun_hpp
