#ifndef effectManager_hpp
#define effectManager_hpp

#include <vector>

#include <boost/shared_ptr.hpp>

#include "effect.hpp"

class spriteManager;

class EffectManager
{
public:
	EffectManager(spriteManager *SM);
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
	spriteManager *mySpriteManager;
    bool active;
};

#endif // #ifndef effectManager_hpp
