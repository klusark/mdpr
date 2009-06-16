#ifndef effect_hpp
#define effect_hpp

#include "genericSprite.hpp"

class Effect : public genericSprite
{
public:
	Effect(const std::string &name);
	~Effect();
	bool inUse;
	void update();
	
};

#endif // #ifndef effect_hpp
