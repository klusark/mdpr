#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../powerup/powerUpManager.hpp"
#include "../enumerations.hpp"
#include "../helpers.hpp"
#include "genericSprite.hpp"
#include "powerup.hpp"
#include "bubble.hpp"

sf::Image Bubble::Image;

Bubble::Bubble(const std::string &name)
	:	genericSprite(name, "bubble", Image),
		powerup(name+"powerup")
{
	spriteType = bubbleType;

	changeAnimation(stringToCRC("bubble"));

	setYVelocity(100.0f);
	setXVelocity(100.0f);
	//powerup.changeAnimation(PUManage->selectRandom());
}

Bubble::~Bubble()
{

}

void Bubble::update()
{
	
	sf::Vector2f position = GetPosition();
	if (position.x >= 640 - 16 || position.x < 0){
		setXVelocity(-getXVelocity());
		if (position.x < 0){
			SetX(1);
		}else if (position.x >= 640 - 16){
			SetX(640 - 15);
		}
	}
	if (position.y >= 400 - 16 || position.y < 0){
		setYVelocity(-getYVelocity());
		if (position.y < 0){
			SetY(1);
		}else if (position.y >= 400 - 16){
			SetY(400 - 15);
		}
	}
	//powerup.update();
	genericSprite::update();
	powerup.SetPosition(GetPosition());
}

void Bubble::draw(sf::RenderWindow &App)
{	
	genericSprite::draw(App);
	App.Draw(powerup);
}
