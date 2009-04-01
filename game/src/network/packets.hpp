#ifndef packets_hpp
#define packets_hpp

#include "../enumerations.hpp"

enum packetIDs
{
	connectPacketID,
	spriteCreationPacketID,
	spriteDeletionPacketID,
	spritePosPacketID,
	errorPacketID,
	keyPacketID,
	animationChangePacketID,
	changePowerUpPacketID,
	needSpritePacketID,
	serverInfoPacketID,
	sendUpdateToMasterPacketID,
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
Size: 15
*/
struct spritePosPacket
{
	packetIDs packetID;
	unsigned short spriteID;
	float x;
	float y;
	bool flipped;
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

/*
Size: 10
*/
struct changePowerUpPacket
{
	packetIDs packetID;

	unsigned short spriteID;
	powerups powerupID;
};

struct needSpritePacket
{
	packetIDs packetID;
	unsigned short stuff;
};

struct serverInfoPacket
{
	packetIDs packetID;
	
};

struct sendUpdateToMasterPacket
{
	packetIDs packetID;
};

#endif // ifndef packets_hpp
