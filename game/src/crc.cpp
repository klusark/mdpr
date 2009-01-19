#include <boost/crc.hpp>
#include <string>
#include <sstream>
#include "crc.hpp"

CRC::CRC()
{
}

CRC::~CRC()
{
}

short CRC::stringToShort(std::string string)
{
	boost::crc_16_type result;
	result.process_bytes(string.c_str(), string.length());
	std::stringstream buf;
	buf << result.checksum();
	//for debugging
	unsigned short returnValue = atoi(buf.str().c_str());
	return returnValue;
}