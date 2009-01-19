#ifndef packets_hpp
#define packets_hpp

enum packetIDs
{
	connectPacketID,
	spriteCreationPacketID,
	spriteDeletionPacketID,
	spritePosPacketID,
	errorPacketID,
	keyPacketID,
	animationChangePacketID,
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

enum spriteTypes
{
	player,
	platform
};

/*
Size: 10+nameLength
*/
struct spriteCreationPacket
{
	packetIDs packetID;
	spriteTypes spriteType;
	unsigned char nameLength;
	char name[255];
};

/*
Size: 6
*/
struct spriteDeletionPacket
{
	packetIDs packetID;
	unsigned short spriteID;
};

/*
Size: 22
*/
struct spritePosPacket
{
	packetIDs packetID;
	unsigned short spriteID;
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

/*
Size: 8
*/
struct animationChangePacket
{
	packetIDs packetID;

	unsigned short spriteID;
	unsigned short animationID;
};

#endif // ifndef packets_hpp
