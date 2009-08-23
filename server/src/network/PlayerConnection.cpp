#include <Poco/NObserver.h>
#include <Poco/Util/Application.h>
#include "PlayerConnection.hpp"
#include "network/packets.hpp"
#include "sprite/player.hpp"
#include "sprite/spriteManager.hpp"
#include "helpers.hpp"
#include "sprite/animation.hpp"

PlayerConnection::PlayerConnection(Poco::Net::SocketAddress newClientAddress, std::string name, bool noSpriteUpdates, GenericSprite* newSprite):
stillAlive(true),
ClientAddress(newClientAddress),
buffer(new char[BUFFER_SIZE]),
noSpriteUpdates(noSpriteUpdates),
name(name),
playerSprite(newSprite)
{
	//socket.connect(ClientAddress);
	unsigned char test = 99;
	socket.sendTo((void *)&test, 1, ClientAddress);

	Reactor.addEventHandler(socket, Poco::NObserver<PlayerConnection, Poco::Net::ReadableNotification>	(*this, &PlayerConnection::onReceivePacket));
	ReactorThread.start(Reactor);
	/*

	*/
}

PlayerConnection::~PlayerConnection()
{
	Reactor.stop();
	ReactorThread.join();
}

void PlayerConnection::onReceivePacket(const Poco::AutoPtr<Poco::Net::ReadableNotification> &)
{
	stillAlive = true;
	socket.receiveFrom(buffer, BUFFER_SIZE, ClientAddress);

	packetType packetID;
	memcpy(&packetID, buffer, sizeof(packetType));
	switch(packetID)
	{
	case keyPacketID:
		{
			keyPacket *packet = (keyPacket *)buffer;
			dynamic_cast<Player *>(playerSprite)->keyMap[packet->key]	= packet->down;
			dynamic_cast<Player *>(playerSprite)->keyMapTwo[packet->key]= packet->down;
		}
		break;

	case testPacketID:
		{
			if (!noSpriteUpdates){
				//Send all the sprite types to the client
				SpriteManager::spriteTypeContainer::iterator iter;
				for(iter = sprite.SpriteTypes.begin(); iter != sprite.SpriteTypes.end(); ++iter){

					spriteTypeCreationPacket packet;
					packet.packetID = spriteTypeCreationPacketID;
					packet.spriteTypeID = iter->first;
					packet.fileNameLength = iter->second.length() + 1;
					strcpy(packet.fileName, iter->second.c_str());
					size_t size = sizeof(spriteTypeCreationPacket) - 255 + packet.fileNameLength;
					socket.sendTo((const void *)&packet, size, ClientAddress);
				}

				{
					//Send all the animations to the client
					SpriteManager::animationPacketContainer::iterator iter;
					for(iter = sprite.Animations.begin(); iter != sprite.Animations.end(); ++iter){
						socket.sendTo((const void *)&iter->second, sizeof(animationCreationPacket), ClientAddress);

					}
				}

				{
					//Send all the sprites to the client
					SpriteManager::spriteContainer::iterator iter;
					for(iter = sprite.Sprites.begin(); iter != sprite.Sprites.end(); ++iter){
						if(iter->second->nonNetworked){
							continue;
						}

						spriteCreationPacket packet;
						packet.packetID = spriteCreationPacketID;
						packet.spriteType = stringToCRC(iter->second->spriteTypeName);
						packet.nameLength = iter->second->name.length() + 1;
						strcpy(packet.name, iter->second->name.c_str());

						positionAndFrameUpdatePacket POSpacket;
						POSpacket.packetID = positionAndFrameUpdatePacketID;
						Position position = iter->second->GetPosition();
						POSpacket.spriteID = iter->first;

						POSpacket.x = position.x;
						POSpacket.y = position.y;
						POSpacket.flipped = iter->second->flipped;
						POSpacket.currentFrame = iter->second->currentAnimation->currentFrame;

						animationChangePacket AnimPacket;
						AnimPacket.packetID = animationChangePacketID;
						AnimPacket.spriteID = iter->first;
						AnimPacket.animationID = iter->second->currentAnimation->CRCName;


						socket.sendTo((const void *)&packet, sizeof(spriteCreationPacket) - 255 + packet.nameLength, ClientAddress);
						socket.sendTo((const void *)&POSpacket, sizeof(positionAndFrameUpdatePacket), ClientAddress);
						socket.sendTo((const void *)&AnimPacket, sizeof(animationChangePacket), ClientAddress);

					}
				}
			}
			Poco::Util::Application::instance().logger().information("Player " + name + " connected from " + ClientAddress.toString());

			{
				//Send the done connecting packet to tell the client that all the info has been sent
				doneConnectingPacket packet;
				packet.packetID = doneConnectingPacketID;
				socket.sendTo((const void *)&packet, sizeof(doneConnectingPacket), ClientAddress);
			}
		}
	case cannotFindSpritePacketID:
		{
			cannotFindSpritePacket *packet = (cannotFindSpritePacket *)buffer;

			if (sprite.Sprites.find(packet->spriteID) != sprite.Sprites.end()){
				spriteCreationPacket spritePacket;
				spritePacket.packetID = spriteCreationPacketID;
				strcpy(spritePacket.name, sprite.Sprites[packet->spriteID]->name.c_str());
				spritePacket.nameLength = name.length() + 1;
				spritePacket.spriteType = stringToCRC(sprite.Sprites[packet->spriteID]->spriteTypeName);
				socket.sendTo((const void *)&spritePacket, sizeof(cannotFindSpritePacket), ClientAddress);
			}
			
			

		}
		break;
	}
}
