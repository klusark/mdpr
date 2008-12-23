#ifndef packets_hpp
#define packets_hpp

enum packetIDs
{
	connectPacketID,
};

struct connectPacket
{
	packetIDs packetID;
	unsigned char nameLength;
	char name[255];
};

#endif //packets_hpp