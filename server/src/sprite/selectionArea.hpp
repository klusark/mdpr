#ifndef selectionArea_hpp
#define selectionArea_hpp

#include <vector>

#include "genericSprite.hpp"

class selectionArea : public genericSprite
{
public:
	selectionArea(const std::string &name, sf::IntRect rect);
	~selectionArea();
	sf::IntRect collisionRect;
	bool collisionChecked;
	spriteTypes typeToSelect;
	void update();
	void draw();
	typedef std::vector<std::string> selectedSpriteContainer;
	selectedSpriteContainer selectedSprites;
	
};

#endif // #ifndef selectionArea_hpp
