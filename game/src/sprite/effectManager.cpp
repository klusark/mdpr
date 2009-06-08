#include <boost/shared_ptr.hpp>

#include "effectManager.hpp"

EffectManager::EffectManager(spriteManager &SM)
	:	active(false),
		currentNumberEffects(0),
		mySpriteManager(SM)
{
	for (;currentNumberEffects < initialNumberOfEffects; ++currentNumberEffects){
		std::string name = "effect";
		char buff[4];
		sprintf(buff, "%d", currentNumberEffects);
		name += buff;
		boost::shared_ptr<genericSprite> newEffect(new Effect(name));
		Effects.push_back(dynamic_cast<Effect *>(newEffect.get()));
		mySpriteManager.registerSprite(newEffect);
	}
}

EffectManager::~EffectManager()
{
}

bool EffectManager::isActive()
{
    return active;
}

void EffectManager::setActive(bool toggle)
{
    active = toggle;
}
