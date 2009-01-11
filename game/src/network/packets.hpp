#ifndef packets_hpp
#define packets_hpp

enum packetIDs
{
	connectPacketID,
	spritePacketID,
	spritePosPacketID,
	errorPacketID,
	keyPacketID,
};

/*
Size: 6+nameLength
*/
struct connectPacket
{
	packetIDs packetID;
	unsigned char nameLength;
	char name[255];
};

/*
Size: 6+nameLength
*/
struct spritePacket
{
	packetIDs packetID;
	unsigned char nameLength;
	char name[255];
};

/*
Size: 24
*/
struct spritePosPacket
{
	packetIDs packetID;
	unsigned int spriteID;
	float x;
	float y;

};

enum errorIDs
{
	nameInUse,

};

/*
Size: 8
*/
struct errorPacket
{
	packetIDs packetID;
	errorIDs errorID;
};

enum keys
{
	keyDown,
	keyUp,
	keyLeft,
	keyRight,
};

/*
Size: 9
*/
struct keyPacket
{
	packetIDs packetID;
	
	keys key;
	bool down;
};

#endif //packets_hpp