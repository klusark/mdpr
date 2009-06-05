#ifndef packets_hpp
#define packets_hpp

#include "../enumerations.hpp"

enum packetIDs
{
	connectPacketID,
	doneConnectingPacketID,
	spriteCreationPacketID,
	spriteDeletionPacketID,
	spritePosPacketID,
	errorPacketID,
	keyPacketID,
	positionAndFrameUpdatePacketID,
	animationChangePacketID,
	changePowerUpPacketID,
	changeBubblePowerUpPacketID,
	needSpritePacketID,
	serverInfoPacketID,
	getServersPacketID,
	serversListPacketID,
	getFullServerInfoPacketID,
	fullServerInfoPacketID,
};

/**
Size: 6+nameLength
Client -> Server
*/
struct connectPacket
{
	packetIDs packetID;
	unsigned char nameLength;
	char name[255];
};

/**
Size: 4
Client <- Server
*/
struct doneConnectingPacket
{
	packetIDs packetID;;
};

/**
Size: 10+nameLength
Client <- Server
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
	float x;
	float y;

	unsigned short spriteID;
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
};

/*
Size: 16
*/
struct positionAndFrameUpdatePacket
{
	packetIDs packetID;
	float x;
	float y;

	unsigned short spriteID;
	unsigned char currentFrame;
	bool flipped;
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

struct fullServerInfoPacket
{
	packetIDs packetID;
};

#endif // #ifndef packets_hpp
