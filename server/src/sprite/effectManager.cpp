#include <boost/shared_ptr.hpp>

#include "spriteManager.hpp"
#include "effectManager.hpp"
#include "helpers.hpp"

EffectManager::EffectManager(spriteManager *SM)
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
		mySpriteManager->registerSprite(newEffect);
	}
}

EffectManager::~EffectManager()
{
}

void EffectManager::addEffect(unsigned short effectID,	float x, float y)
{
	for (unsigned short i = 0; i < Effects.size(); ++i){
		if (!Effects[i]->inUse){
			Effects[i]->inUse = true;
			Effects[i]->SetX(x);
			Effects[i]->SetY(y);
			Effects[i]->changeAnimation(effectID);

			break;
		}
	}
}

void EffectManager::addEffect(std::string effectID,	float x, float y)
{
	addEffect(stringToCRC(effectID), x, y);
}

bool EffectManager::isActive()
{
    return active;
}

void EffectManager::setActive(bool toggle)
{
    active = toggle;
}
