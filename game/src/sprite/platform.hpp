#ifndef platform_hpp
#define platform_hpp

#include "genericSprite.hpp"
#include <SFML/Graphics/Image.hpp>

class Platform : public genericSprite
{
public:
	Platform(const std::string &name);
	~Platform();
	static sf::Image Image;
	
};

#endif // ifndef platform_hpp
