#ifndef genericPowerUp_hpp
#define genericPowerUp_hpp

#include <Poco/SharedPtr.h>

class GenericSprite;

class genericPowerUp
{
public:
	genericPowerUp(GenericSprite *owner);
	~genericPowerUp();
	virtual void onActionKey();
	virtual void update();

	GenericSprite *owner;
};

#endif // ifndef genericPowerUp_hpp
