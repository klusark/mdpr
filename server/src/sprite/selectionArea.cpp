#include <cmath> //for abs

#include "enumerations.hpp"
#include "genericSprite.hpp"
#include "selectionArea.hpp"
#include "helpers.hpp"
#include "spriteManager.hpp"

selectionArea::selectionArea(const std::string &name, sf::IntRect rect)
	:	GenericSprite(name, "selectionArea"),
		collisionChecked(false)
{
	currentState = aliveState;
	spriteType = selectionAreaType;
	collisionRect = rect;
	nonNetworked = true;

}

selectionArea::~selectionArea()
{

}

void selectionArea::update()
{
	GenericSprite::update();
}

Poco::SharedPtr<GenericSprite> selectionArea::selectClosest(Position pos, bool x, bool y)
{
	unsigned short lowest;
	//give the shortest a very high value
	float shortestSoFar = float((unsigned int)-1);

	for (unsigned short i = 0; i < selectedSprites.size(); ++i){
		float xDistance, yDistance, totalDistance;
		xDistance = abs(selectedSprites[i]->GetX() - pos.x);
		yDistance = abs(selectedSprites[i]->GetY() - pos.y);
		totalDistance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
		if (x && y){
			if (shortestSoFar > totalDistance){
				shortestSoFar = totalDistance;
				lowest = i;
			}
		}else if (x){
			if (shortestSoFar > xDistance){
				shortestSoFar = xDistance;
				lowest = i;
			}
		}else if (y){
			if (shortestSoFar > yDistance){
				shortestSoFar = yDistance;
				lowest = i;
			}
		}
	}
	return selectedSprites[lowest];
}

Poco::SharedPtr<GenericSprite> selectionArea::selectFarthest(Position pos, bool x, bool y)
{
	return selectedSprites[0];
}
