#ifndef packets_hpp
#define packets_hpp

#include "enumerations.hpp"
#include <string>

enum packetIDs
{
	connectPacketID,
	doneConnectingPacketID,
	connectionAcceptedPacketID,
	spriteTypeCreationPacketID,
	animationCreationPacketID,
	spriteCreationPacketID,
	spriteDeletionPacketID,
	spritePosPacketID,
	errorPacketID,
	keyPacketID,
	positionAndFrameUpdatePacketID,
	animationChangePacketID,
	cannotFindSpritePacketID,
	serverInfoPacketID,
	getServersPacketID,
	serversListPacketID,
	getFullServerInfoPacketID,
	fullServerInfoPacketID,
};

/*!
Size: 6+nameLength
Client -> Server
*/
struct connectPacket
{
	packetIDs packetID;
	unsigned char nameLength;
	char name[255];
};

/*!
Size: 4
Client <- Server
*/
struct doneConnectingPacket
{
	packetIDs packetID;
};

/*!
Sent when the server has accpeted the client
Size: 4
Client <- Server
*/
struct connectionAcceptedPacket
{
	packetIDs packetID;
};

/*!
Creates a new sprite type on the client
Size: 7 + fileNameLength
Client <- Server
*/
struct spriteTypeCreationPacket
{
	packetIDs packetID;
	unsigned short spriteTypeID;
	unsigned char fileNameLength;
	char fileName[255];
};

/*!
Creates a new animation on the client
Size: 16
Client <- Server
*/
struct animationCreationPacket
{
	packetIDs packetID;
	unsigned short animationID, startX, startY, width, height, padding;
};

/*!
Size: 7 + nameLength
Client <- Server
*/
struct spriteCreationPacket
{
	packetIDs packetID;
	unsigned short spriteType;
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

struct cannotFindSpritePacket
{
	packetIDs packetID;
	unsigned short spriteID;
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

struct fullServerEntry
{
	serverEntry entry;
	unsigned short numPlayers;
	unsigned short maxPlayers;
	std::string serverName;
};

struct fullServerInfoPacket
{
	packetIDs packetID;
	unsigned short numPlayers, maxPlayers, port;
	char serverName[256];
};

#endif // #ifndef packets_hpp
