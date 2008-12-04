#include "packets.hpp"
#include "network.hpp"
#include "packetHandlers.hpp"
#include <iostream>

namespace engine
{
	namespace network
	{
		namespace handlers
		{

			inline packet::packetTypes selectType(char *message)
			{
				return *(reinterpret_cast<packet::packetTypes *>(message));
			}

			void serverRecvHandler(char *message, int length)
			{
				packet::packetTypes type = selectType(message);
				switch (type){
					case packet::connect:
						serverRecvConnect(message);
						if (length > sizeof(packet::connectPacket)){
							serverRecvHandler(message + sizeof(packet::connectPacket), length - sizeof(packet::connectPacket));
						}
						break;
					default:
						std::cout<<"Error In Recvd Packet";
				}
			}

			void clientRecvHandler(char *message, int length)
			{
				packet::packetTypes type = selectType(message);
				switch (type){
					case packet::connect:
						//clientRecvConnect(message);
						if (length > sizeof(packet::connectPacket)){
							clientRecvHandler(message + sizeof(packet::connectPacket), length - sizeof(packet::connectPacket));
						}
						break;
					case packet::sprite:
						clientRecvSprite(message);
						if (length > sizeof(packet::spritePacket)){
							clientRecvHandler(message + sizeof(packet::spritePacket), length - sizeof(packet::spritePacket));
						}
						break;
					default:
						std::cout<<"Error In Recvd Packet";
				}
			}

			void clientRecvSprite(char *message)
			{
				packet::spritePacket *recvdPacket = new(packet::spritePacket);
				memcpy(recvdPacket, message, sizeof(packet::spritePacket));
				std::cout<<recvdPacket->name;

			}

			void serverRecvConnect(char *message)
			{
				packet::connectPacket *recvdPacket = new(packet::connectPacket);
				memcpy(recvdPacket, message, sizeof(packet::connectPacket));
				
			}
		}
	}
}