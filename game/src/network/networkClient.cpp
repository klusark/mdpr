#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

#include <iostream>

#include "../enumerations.hpp"
#include "../MDPRGame.hpp"
#include "../sprite/bubble.hpp"
#include "../sprite/platform.hpp"
#include "../sprite/player.hpp"
#include "../sprite/effect.hpp"
#include "../sprite/spriteManager.hpp"
#include "packets.hpp"
#include "networkClient.hpp"

using boost::asio::ip::udp;

networkClient::networkClient()
	:	socket(ioService, udp::endpoint()),
		inGame(true),
		connected(false),
		totalBytesRecived(0),
		bytesInLastFive(0),
		currentState(idleState)
{


	socket.async_receive_from(boost::asio::buffer(buffer), receiverEndpoint, boost::bind(&networkClient::onReceivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	for (short i = 0; i < numIOServiceThreads; ++i){
		ioServiceThreadPool.create_thread(boost::bind(&networkClient::ioServiceThread, this));
	}

		
	/*for (short i = 0; i <= numServerUpdateThreads-1; ++i){
		serverListUpdateThreads.create_thread(boost::bind(&networkClient::serverListUpdateThread, this, i));
	}*/
}

networkClient::~networkClient()
{
	ioService.stop();
	ioServiceThreadPool.join_all();
	//delete ioThread;

}

bool networkClient::connect()
{
	try
	{
		{
			connectPacket packet;
			packet.packetID = connectPacketID;
			packet.nameLength = MDPR->playerName.length();
			strcpy(packet.name, MDPR->playerName.c_str());

			udp::resolver resolver(ioService);
			udp::resolver::query query(udp::v4(), MDPR->serverIP, MDPR->serverPort);
			receiverEndpoint = *resolver.resolve(query);
			
			socket.send_to(boost::asio::buffer((const void *)&packet, 6 + packet.nameLength), receiverEndpoint);
			currentState = connectingState;
		}

		{
			getServersPacket packet;
			packet.packetID = getServersPacketID;

			udp::resolver resolver(ioService);
			udp::resolver::query query(udp::v4(), MDPR->serverIP, "9937");
			masterServerEndpoint = *resolver.resolve(query);
			
			socket.send_to(boost::asio::buffer((const void *)&packet, 4), masterServerEndpoint);
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		return false;
	}
	connected = true;
	return true;
}

void networkClient::onReceivePacket(const boost::system::error_code& error, size_t bytesReceived)
{
	totalBytesRecived += bytesReceived;
	bytesInLastFive += bytesReceived;
	float time = timer.GetElapsedTime();
	if (time >= 5) {
		float bps = bytesInLastFive/time;
		std::cout << bytesInLastFive << " bytes in " << time << " seconds = " << bps << " BPS" << std::endl;
		timer.Reset();
		bytesInLastFive = 0;
	}
	if (error){
		std::cout << error.message() << std::endl;
		
	}else{
		packetIDs packetID;
		memcpy(&packetID, buffer, 4);

		switch(packetID)
		{
		case spriteCreationPacketID:
			{
				spriteCreationPacket *packet = (spriteCreationPacket *)buffer;
				switch(packet->spriteType)
				{
				case playerType:
					{
						boost::shared_ptr<genericSprite> newSprite(new Player(packet->name));
						sprite.registerSprite(newSprite);
					}
					break;
				case platformType:
					{
						boost::shared_ptr<genericSprite> newSprite(new Platform(packet->name));
						sprite.registerSprite(newSprite);
					}
					break;
				case bubbleType:
					{
						boost::shared_ptr<genericSprite> newSprite(new Bubble(packet->name));
						sprite.registerSprite(newSprite);
					}
					break;
				case effectType:
					{
						boost::shared_ptr<genericSprite> newSprite(new Effect(packet->name));
						sprite.registerSprite(newSprite);
					}
					break;
				}
			}
			break;
		case spritePosPacketID:
			{
				spritePosPacket *packet = (spritePosPacket *)buffer;
				boost::mutex::scoped_lock lock(sprite.spriteMutex);
				if (sprite.Sprites.find(packet->spriteID) == sprite.Sprites.end()){
					std::cout << "Could not find sprite" << std::endl;
					break;
				}
				sprite.Sprites[packet->spriteID]->SetX(packet->x);
				sprite.Sprites[packet->spriteID]->SetY(packet->y);
				sprite.Sprites[packet->spriteID]->flipped = packet->flipped;
			}
			break;
		case spriteDeletionPacketID:
			{
				spriteDeletionPacket *packet = (spriteDeletionPacket *)buffer;
				if (sprite.Sprites.find(packet->spriteID) == sprite.Sprites.end()){
					std::cout << "Can not find sprite" << std::endl;
				}
				boost::mutex::scoped_lock lock(sprite.spriteMutex);
				sprite.Sprites.erase(sprite.Sprites.find(packet->spriteID));

				
			}
			break;
		case errorPacketID:
			{
				errorPacket *packet = (errorPacket *)buffer;
				switch(packet->errorID)
				{
				case nameInUse:
						std::cout << "Error: Name already in use" << std::endl;
					break;
				}
				
			}
			break;
		case animationChangePacketID:
			{
				animationChangePacket *packet = (animationChangePacket *)buffer;
				boost::mutex::scoped_lock lock(sprite.spriteMutex);
				if (sprite.Sprites.find(packet->spriteID) == sprite.Sprites.end()){
					std::cout << "Could not find sprite" << std::endl;
					break;
				}
				sprite.Sprites[packet->spriteID]->changeAnimation(packet->animationID);
				//sprite.Sprites[packet->spriteID]->currentAnimation->currentFrame = packet->currentFrame;
			}
			break;
		case positionAndFrameUpdatePacketID:
			{
				positionAndFrameUpdatePacket *packet = (positionAndFrameUpdatePacket *)buffer;
				boost::mutex::scoped_lock lock(sprite.spriteMutex);
				if (sprite.Sprites.find(packet->spriteID) == sprite.Sprites.end()){
					std::cout << "Could not find sprite" << std::endl;
					break;
				}
				sprite.Sprites[packet->spriteID]->SetX(packet->x);
				sprite.Sprites[packet->spriteID]->SetY(packet->y);
				sprite.Sprites[packet->spriteID]->flipped = packet->flipped;
				sprite.Sprites[packet->spriteID]->currentAnimation->currentFrame = packet->currentFrame;
			}
		case serversListPacketID:
			{
				serversListPacket *packet = (serversListPacket *)buffer;
				for (unsigned short i = 0; i < packet->numServers; ++i){
					fullServerEntry newEntry;
					memcpy((void *)&newEntry.entry, (void *)&packet->serverList[i], sizeof(serverEntry));
					serverList.push_back(newEntry);
					serversToUpdate[0].push_back(&newEntry);
				}
			}
			break;
		case changePowerUpPacketID:
			{
				changePowerUpPacket *packet = (changePowerUpPacket *)buffer;
				if (sprite.Sprites.find(packet->spriteID) == sprite.Sprites.end()){
					std::cout << "Can not find sprite" << std::endl;
				}
				Bubble *tempSprite;
				if (sprite.Sprites[packet->spriteID]->spriteType == bubbleType){
					tempSprite = dynamic_cast<Bubble *>(sprite.Sprites[packet->spriteID].get());
				}
				tempSprite->powerup.changeAnimation(packet->powerupID);
			}
			break;
		case fullServerInfoPacketID:
			{

			}
			break;
		case connectionAcceptedPacketID:

			break;
		case doneConnectingPacketID:
			currentState = connectedState;

			break;
		default:
			std::cout << "onReceivePacket: Could not identify packet" << std::endl;
			break;

		}
	}
	socket.async_receive_from(boost::asio::buffer(buffer), receiverEndpoint, boost::bind(&networkClient::onReceivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void networkClient::sendKeyPress(sf::Key::Code key, bool down)
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

	socket.send_to(boost::asio::buffer((const void *)&packet, 9), receiverEndpoint);
}

void networkClient::serverListUpdateThread(int i)
{
	while (1){
		if (serversToUpdate[i].size() == 0){
			Sleep(2);
		}else{
			boost::asio::io_service ioService;
			udp::resolver resolver(ioService);
			std::string test;
			char *buffers;
			buffers = new char[6];
			for (int x = 0; x < 4; ++x){
				char asdf[3];
				sprintf(asdf, "%d", serversToUpdate[i][0]->entry.ip[x]);
				test += asdf;
				if (x != 3){
					test += ".";
				}
			}
			char *buffer;
			buffer = new char[6];
			sprintf(buffer, "%d", serversToUpdate[i][0]->entry.port);
			udp::resolver::query query(udp::v4(), test, buffer);
			udp::endpoint receiverEndpoint = *resolver.resolve(query);
			getFullServerInfoPacket packet;
			packet.packetID = getFullServerInfoPacketID;
			socket.send_to(boost::asio::buffer((const void *)&packet, 4), receiverEndpoint);
			serversToUpdate[i].erase(serversToUpdate[i].begin());
		}
	}
}

void networkClient::ioServiceThread()
{
	try{
		ioService.run();
	}catch (std::exception& e){
		std::cout << "Exception: " << e.what() << std::endl;
	}catch(...){
		std::cout << "Unknown Exception caught" << std::endl; 
	}
}
