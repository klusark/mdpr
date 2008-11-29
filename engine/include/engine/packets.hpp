#ifndef packets_hpp
#define packets_hpp
enum packetTypes
{
	connect,
};
struct connectPacket
{
	const static unsigned short type = connect;
	char name[32];
};
#endif