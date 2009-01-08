#ifndef packets_hpp
#define packets_hpp

enum packetIDs
{
	connectPacketID,
	spritePacketID,
	spritePosPacketID,
};

struct connectPacket
{
	packetIDs packetID;
	unsigned char nameLength;
	char name[255];
};

struct spritePacket
{
	packetIDs packetID;
	unsigned char nameLength;
	char name[255];
};

struct spritePosPacket
{
	packetIDs packetID;
	unsigned int spriteID;
	float x;
	float y;

};

#endif //packets_hpp