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
	typedef std::vector<boost::shared_ptr<genericSprite> > selectedSpriteContainer;
	selectedSpriteContainer selectedSprites;

	//!Selects the closest sprite in the area
	/*!
	\param x when true x is included in distance calculations
	\param y when true y is included in distance calculations
	\param pos the position to check from
	\return pointer to the closest sprite
	*/
	boost::shared_ptr<genericSprite> selectClosest(Position pos, bool x = true, bool y = true);

	//!Selects the farthest sprite in th area
	/*!
	\param x when true x is included in distance calculations
	\param y when true y is included in distance calculations
	\param pos the position to check from
	\return pointer to the farthest sprite
	*/
	boost::shared_ptr<genericSprite> selectFarthest(Position pos, bool x = true, bool y = true);
	
};

#endif // #ifndef selectionArea_hpp
