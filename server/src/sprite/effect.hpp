#ifndef effect_hpp
#define effect_hpp

#include "genericSprite.hpp"

class Effect : public GenericSprite
{
public:
	Effect(const std::string &name);
	~Effect();
	bool inUse;
	void update();
	static GenericSprite::collidesWithContainer colidesWith;
	GenericSprite::collidesWithContainer getCollidesWith() const {return colidesWith;};
	
};

#endif // #ifndef effect_hpp
