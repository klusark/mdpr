#ifndef effect_hpp
#define effect_hpp

#include <SFML/Graphics/Image.hpp>
#include "genericSprite.hpp"

class Effect : public genericSprite
{
public:
	Effect(const std::string &name);
	~Effect();
	static sf::Image Image;
	bool inUse;
	void update();
	
};

#endif // #ifndef effect_hpp
