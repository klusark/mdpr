#ifndef helpers_hpp
#define helpers_hpp

#include <SFML\Graphics\Rect.hpp>

short stringToCRC(std::string string);

sf::IntRect XYWHToLTRB(int x, int y, int w, int h);

#endif // ifndef helpers_hpp
