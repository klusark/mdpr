#include <exception>
#include <SFML/System/Sleep.hpp>
#include <Poco/NObserver.h>
#include <sstream>

#include "enumerations.hpp"
#include "MDPRGame.hpp"

#include "sprite/clientSpriteManager.hpp"
#include "packets.hpp"
#include "networkClient.hpp"
#include "menu/menuManager.hpp"


NetworkClient::NetworkClient():	
inGame(true),
connected(false),
totalBytesRecived(0),
bytesInLastFive(0),
currentState(idleState),
buffer(new char[BUFFER_SIZE]),
serverListUpdateTimer(200, 200)
{

	reactor.addEventHandler(socket, Poco::NObserver<NetworkClient, Poco::Net::ReadableNotification>(*this, &NetworkClient::onReceivePacket));
	
	thread.start(reactor);

	serverListUpdateTimer.start(Poco::TimerCallback<NetworkClient>(*this, &NetworkClient::serverListUpdateThread));
}

NetworkClient::~NetworkClient()
{
	reactor.stop();
	thread.join();
}

void NetworkClient::connectToServer(std::string ip, std::string port, bool noSpriteUpdate, std::string playerName)
{
	connectPacket packet;
	packet.packetID = connectPacketID;
	packet.nameLength = playerName.length();
	packet.noSpriteUpdates = noSpriteUpdate;
	strcpy(packet.name, playerName.c_str());

	serverAddress = Poco::Net::SocketAddress(ip, port);
	
	socket.sendTo((const void *)&packet, sizeof(connectPacket) +  packet.nameLength - 255, serverAddress);
	currentState = connectingState;
	connected = true;
}

void NetworkClient::connectToServer(serverEntry entry, bool noSpriteUpdate, std::string playerName)
{
	std::stringstream ipstream;

	for (int x = 0; x < 4; ++x){
		ipstream << (int)entry.ip[x];
		if (x != 3){
			ipstream << ".";
		}
	}
	
	std::stringstream portstream;
	portstream << entry.port;

	connectToServer(ipstream.str(), portstream.str(), noSpriteUpdate, playerName);
}

void NetworkClient::connectToMaster()
{
	getServersPacket packet;
	packet.packetID = getServersPacketID;
	Poco::Net::SocketAddress masterServerAddress(Poco::Util::Application::instance().config().getString("master.ip"), Poco::Util::Application::instance().config().getString("master.port"));
	try{
	socket.sendTo((const void *)&packet, 4, masterServerAddress);
	}catch(...){}
}

void NetworkClient::onReceivePacket(const Poco::AutoPtr<Poco::Net::ReadableNotification>& pNf)
{
	Poco::Net::SocketAddress socketAddress;
	
	try{
		socket.receiveFrom(buffer, BUFFER_SIZE, socketAddress);

		packetType packetID;
		memcpy(&packetID, buffer, sizeof(packetType));

		switch(packetID)
		{
		case spriteCreationPacketID:
			{
				spriteCreationPacket *packet = (spriteCreationPacket *)buffer;
				Poco::SharedPtr<ClientSprite> newSprite(new ClientSprite(packet->name));
				newSprite->SetImage(*sprite->Images[packet->spriteType].get());
				sprite->registerSprite(newSprite);
				
			}
			break;
		case spriteTypeCreationPacketID:
			{
				spriteTypeCreationPacket *packet = (spriteTypeCreationPacket *)buffer;
				Poco::SharedPtr<sf::Image> Image(new sf::Image);
				std::string fileName;
				fileName += "data/";
				fileName += packet->fileName;
				if (!Image->LoadFromFile(fileName)){
					getImagePacket newPacket;
					newPacket.packetID = getImagePacketID;
					newPacket.spriteID = packet->spriteTypeID;
					socket.sendTo((const void *)&newPacket, sizeof(getImagePacketID), socketAddress);
				}
				
				Image->SetSmooth(false);
				Image->CreateMaskFromColor(sf::Color(255,255,255));
				sprite->Images[packet->spriteTypeID] = Image;
			}
			break;
		case animationCreationPacketID:
			{
				animationCreationPacket *packet = (animationCreationPacket *)buffer;
				sprite->Animations[packet->animationID] = *packet;
			}
			break;
		case spritePosPacketID:
			{
				spritePosPacket *packet = (spritePosPacket *)buffer;
				Poco::ScopedLock<Poco::Mutex> lock(sprite->spriteMutex);
				if (sprite->Sprites.find(packet->spriteID) == sprite->Sprites.end()){
					cannotFindSpritePacket newPacket;
					newPacket.packetID = cannotFindSpritePacketID;
					newPacket.spriteID = packet->spriteID;
					socket.sendTo((const void *)&newPacket, sizeof(cannotFindSpritePacket), socketAddress);
					//std::cout << "Could not find sprite" << std::endl;
					break;
				}
				sprite->Sprites[packet->spriteID]->SetX(packet->x);
				sprite->Sprites[packet->spriteID]->SetY(packet->y);
				sprite->Sprites[packet->spriteID]->flipped = packet->flipped;
			}
			break;
		case spriteDeletionPacketID:
			{
				spriteDeletionPacket *packet = (spriteDeletionPacket *)buffer;
				if (sprite->Sprites.find(packet->spriteID) == sprite->Sprites.end()){
					Poco::Util::Application::instance().logger().warning("Can not find sprite");
					//std::cout << "Can not find sprite" << std::endl;
				}
				Poco::ScopedLock<Poco::Mutex> lock(sprite->spriteMutex);
				sprite->Sprites.erase(sprite->Sprites.find(packet->spriteID));

				
			}
			break;
		case errorPacketID:
			{
				errorPacket *packet = (errorPacket *)buffer;
				switch(packet->errorID)
				{
				case nameInUse:
						Poco::Util::Application::instance().logger().error("Error: Name already in use");
					break;
				}
				
			}
			break;
		case animationChangePacketID:
			{
				animationChangePacket *packet = (animationChangePacket *)buffer;
				Poco::ScopedLock<Poco::Mutex> lock(sprite->spriteMutex);
				if (sprite->Sprites.find(packet->spriteID) == sprite->Sprites.end()){
					Poco::Util::Application::instance().logger().warning("Can not find sprite");
					break;
				}
				sprite->Sprites[packet->spriteID]->currentAnimationID = packet->animationID;
			}
			break;
		case positionAndFrameUpdatePacketID:
			{
				positionAndFrameUpdatePacket *packet = (positionAndFrameUpdatePacket *)buffer;
				Poco::ScopedLock<Poco::Mutex> lock(sprite->spriteMutex);
				if (sprite->Sprites.find(packet->spriteID) == sprite->Sprites.end()){
					Poco::Util::Application::instance().logger().warning("Can not find sprite");
					break;
				}
				sprite->Sprites[packet->spriteID]->SetX(packet->x);
				sprite->Sprites[packet->spriteID]->SetY(packet->y);
				sprite->Sprites[packet->spriteID]->flipped = packet->flipped;
				sprite->Sprites[packet->spriteID]->currentFrame = packet->currentFrame;
			}
			break;
		case serversListPacketID:
			{
				serversListPacket *packet = (serversListPacket *)buffer;
				for (unsigned short i = 0; i < packet->numServers; ++i){
					fullServerEntry newEntry;
					memcpy((void *)&newEntry.entry, (void *)&packet->serverList[i], sizeof(serverEntry));
					//serverList.push_back(newEntry);
					serversToUpdate[0].push_back(newEntry);
				}
			}
			break;
		case fullServerInfoPacketID:
			{
				fullServerInfoPacket *packet = (fullServerInfoPacket *)buffer;
				fullServerEntry newEntry;

				memcpy(newEntry.entry.ip, socketAddress.addr()->sa_data+2, 4);
				newEntry.entry.port = packet->port;
				newEntry.maxPlayers = packet->maxPlayers;
				newEntry.numPlayers = packet->numPlayers;
				newEntry.serverName = packet->serverName;
				menu->addServer(newEntry);
				serverList.push_back(newEntry);

			}
			break;
		case connectionAcceptedPacketID:

			break;
		case doneConnectingPacketID:
			currentState = connectedState;

			break;
		default:
			Poco::Util::Application::instance().logger().error("onReceivePacket: Could not identify packet");
			break;

		}
	}catch (Poco::Exception& e){
		std::string message = "Poco::Exception: "; 
		message += e.what();
		Poco::Util::Application::instance().logger().error(message);
	}catch (std::exception& e){
		std::string message = "std::exception: "; 
		message += e.what();
		Poco::Util::Application::instance().logger().error(message);
	}
}

void NetworkClient::sendKeyPress(sf::Key::Code key, bool down)
{
	if (!inGame){
		return;
	}
	keyPacket packet;
	packet.packetID = keyPacketID;
	packet.down = down;
	if (key == MDPR->controls.right){
		packet.key = keyRight;
	}else if (key == MDPR->controls.left){
		packet.key = keyLeft;
	}else if (key == MDPR->controls.use){
		packet.key = keyAction;
	}else if (key == MDPR->controls.up){
		packet.key = keyUp;
	}else if (key == MDPR->controls.down){
		packet.key = keyDown;
	}else{
		return;
	}

	socket.sendTo((const void *)&packet, 9, serverAddress);
}

void NetworkClient::serverListUpdateThread(Poco::Timer&)
{
	try{
		int i = 0;
		while (serversToUpdate[i].size() != 0){
			std::stringstream ss;
			for (int x = 0; x < 4; ++x){
				//casted to an int to trick string stream into thinking that it is a number and not a character
				ss << (int)serversToUpdate[i][0].entry.ip[x];
				if (x != 3){
					ss << ".";
				}
			}
			Poco::Net::SocketAddress address(ss.str(), serversToUpdate[i][0].entry.port);
			getFullServerInfoPacket packet;
			packet.packetID = getFullServerInfoPacketID;
			try{
				socket.sendTo((const void *)&packet, 4, address);
			}catch(...){
				Poco::Util::Application::instance().logger().warning("serverListUpdateThread1");
			}
			serversToUpdate[i].erase(serversToUpdate[i].begin());
		}
	}catch(...){
		Poco::Util::Application::instance().logger().warning("serverListUpdateThread2");
	}
}
