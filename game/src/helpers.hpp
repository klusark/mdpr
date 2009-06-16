#ifndef helpers_hpp
#define helpers_hpp

#include <SFML/Graphics/Rect.hpp>

unsigned short stringToCRC(std::string string);

sf::IntRect XYWHToLTRB(int x, int y, int w, int h);

struct Rect
{
	int x,y,w,h;
};

struct RectLTRB
{
	int Left,Top,Right,Bottom;
};

#endif // #ifndef helpers_hpp
