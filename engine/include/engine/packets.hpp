#ifndef packets_hpp
#define packets_hpp

enum packetTypes
{
	connect,
};

/**
 * Connect Packet
 * Size 34
 */
struct connectPacket
{
	const static unsigned short type = connect;
	char name[32];

};

#endif
