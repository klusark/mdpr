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
	changeBubblePowerUpPacketID,
	needSpritePacketID,
	serverInfoPacketID,
	getServersPacketID,
	serversListPacketID,
	getFullServerInfoPacketID,
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
	unsigned char currentFrame;
	//bool paused, reset;
};

/*
Size: 10
*/
struct changePowerUpPacket
{
	packetIDs packetID;

	unsigned short spriteID;
	unsigned short powerupID;
};

struct changeBubblePowerUpPacket
{
	packetIDs packetID;

	unsigned short spriteID;
	unsigned short powerupID;
};

struct needSpritePacket
{
	packetIDs packetID;
	unsigned short stuff;
};

struct serverInfoPacket
{
	packetIDs packetID;
	short port;	
};

/*
Send to master server to get list of servers
*/
struct getServersPacket
{
	packetIDs packetID;
};

struct serverEntry
{
	unsigned char ip[4];
	unsigned short port;
};

/*
Contains as many servers as possble.
from master server to client.
Size: 197
*/
struct serversListPacket
{
	packetIDs packetID;
	unsigned char numServers;
	serverEntry serverList[32];
};

struct getFullServerInfoPacket
{
	packetIDs packetID;
};

#endif // ifndef packets_hpp
