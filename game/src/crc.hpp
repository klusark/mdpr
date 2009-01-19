#ifndef crc_hpp
#define crc_hpp

#include <boost/crc.hpp>

class CRC
{
public:
	CRC();
	~CRC();
	short stringToShort(std::string string);
};

#endif // ifndef crc_hpp
