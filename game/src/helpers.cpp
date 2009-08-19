#include <Poco/Checksum.h>
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include <vector>
#include "helpers.hpp"

unsigned short stringToCRC(std::string string)
{
	Poco::Checksum checksum;
	checksum.update(string);
	//Converts it to a short. looses half the number... should still be enough variation
	unsigned short val = static_cast<unsigned short>(checksum.checksum());
	return val;
}

sf::IntRect XYWHToLTRB(int x, int y, int w, int h)
{
	sf::IntRect rect(x, y, x+w, y+h);
	return rect;
}

std::vector<std::string> splitString(std::string str, std::string delim)
{
	std::vector<std::string> cutString;
	unsigned int cutAt;
	while((cutAt = str.find_first_of(delim)) != str.npos ){
		if(cutAt > 0){
			cutString.push_back(str.substr(0, cutAt));
		}
		str = str.substr(cutAt+1);
	}
	if(str.length() > 0){
		cutString.push_back(str);
	}
	return cutString;
}
