#include <boost/crc.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include <sstream>
#include "helpers.hpp"


short stringToCRC(std::string string)
{
	boost::crc_16_type result;
	result.process_bytes(string.c_str(), string.length());
	std::stringstream buf;
	buf << result.checksum();
	//for debugging
	unsigned short returnValue = atoi(buf.str().c_str());
	return returnValue;
}

sf::IntRect XYWHToLTRB(int x, int y, int w, int h)
{
	sf::IntRect rect(x, y, x+w, y+h);
	return rect;
}