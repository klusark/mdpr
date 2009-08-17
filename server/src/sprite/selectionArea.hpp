#ifndef selectionArea_hpp
#define selectionArea_hpp

#include <vector>
#include <SFML/Graphics/Rect.hpp>

#include "genericSprite.hpp"

class selectionArea : public GenericSprite
{
public:
	selectionArea(const std::string &name, sf::IntRect rect);
	~selectionArea();
	sf::IntRect collisionRect;
	bool collisionChecked;
	spriteTypes typeToSelect;
	void update();

	virtual GenericSprite::collidesWithContainer getCollidesWith();

	typedef std::vector<Poco::SharedPtr<GenericSprite> > selectedSpriteContainer;
	selectedSpriteContainer selectedSprites;

	//!Selects the closest sprite in the area
	/*!
	\param x when true x is included in distance calculations
	\param y when true y is included in distance calculations
	\param pos the position to check from
	\return pointer to the closest sprite
	*/
	Poco::SharedPtr<GenericSprite> selectClosest(Position pos, bool x = true, bool y = true);

	//!Selects the farthest sprite in th area
	/*!
	\param x when true x is included in distance calculations
	\param y when true y is included in distance calculations
	\param pos the position to check from
	\return pointer to the farthest sprite
	*/
	Poco::SharedPtr<GenericSprite> selectFarthest(Position pos, bool x = true, bool y = true);
	
};

#endif // #ifndef selectionArea_hpp
