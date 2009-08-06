#ifndef effectManager_hpp
#define effectManager_hpp

#include <vector>

#include <Poco/SharedPtr.h>

#include "effect.hpp"

class SpriteManager;

class EffectManager
{
public:
	EffectManager(SpriteManager *SM);
	~EffectManager();
	typedef std::vector<Effect *> effectContainer;

	effectContainer Effects;

	bool isActive();
	void setActive(bool toggle);

	void addEffect(unsigned short effectID,	float x, float y);
	void addEffect(std::string effectID,	float x, float y);

	const static unsigned short initialNumberOfEffects = 2;
	const static unsigned short minimumExtraEffects = 2;
	unsigned short currentNumberEffects;

private:
	SpriteManager *mySpriteManager;
    bool active;
};

#endif // #ifndef effectManager_hpp
