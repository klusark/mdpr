#ifndef helpers_hpp
#define helpers_hpp

#include <SFML/Graphics/Rect.hpp>
#include <string>
#include <vector>

unsigned short stringToCRC(std::string string);

sf::IntRect XYWHToLTRB(int x, int y, int w, int h);

//!split a string
/*!
@param str the string to split
@param delim the string to split between
*/
std::vector<std::string> splitString(std::string str, std::string delim);

#endif // #ifndef helpers_hpp
