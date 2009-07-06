//#include <boost/crc.hpp>
#include <Poco/Checksum.h>
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include <sstream>
#include "helpers.hpp"

unsigned short stringToCRC(std::string string)
{
	/*boost::crc_32_type result;
	result.process_bytes(string.c_str(), string.length());
	std::stringstream buf;
	buf << result.checksum();
	//for debugging
	unsigned int returnValue;
	returnValue = atoi(buf.str().c_str());*/
	Poco::Checksum checksum;
	checksum.update(string);
	unsigned short val = checksum.checksum();
	return val;
}

sf::IntRect XYWHToLTRB(int x, int y, int w, int h)
{
	sf::IntRect rect(x, y, x+w, y+h);
	return rect;
}
