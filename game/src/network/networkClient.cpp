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
#include "../sprite/spriteManager.hpp"
#include "packets.hpp"
#include "networkClient.hpp"

using boost::asio::ip::udp;
struct thread
{
public:
	thread(boost::asio::io_service &ioService) 
		:	ioService(ioService)
	{}
	void operator()(){
		try{
			ioService.run();
		}catch(...){
		}
	}
private:
	boost::asio::io_service& ioService;
};

struct serverListUpdateThread
{
public:
	serverListUpdateThread(networkClient::fullServerContainter &serversNeedingUpdate) 
		:	serversToUpdate(serversNeedingUpdate)
	{}
	void operator()(){
		while (1){
			if (serversToUpdate.size() == 0){
				Sleep(2);
			}
		}
		
	}
private:
	networkClient::fullServerContainter serversToUpdate;
};

networkClient::networkClient()
	:	socket(ioService, udp::endpoint(udp::v4(), 45986)),
		inGame(true),
		connected(false)
{


	socket.async_receive_from(boost::asio::buffer(buffer), receiverEndpoint, boost::bind(&networkClient::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	thread threads(ioService);
	ioThread = new boost::thread(threads);

		
	for (short i = 0; i<numServerUpdateThreads; ++i){
		serverListUpdateThread thread(serversToUpdate[i]);
		serverListUpdateThreads.create_thread(thread);
	}


}

networkClient::~networkClient()
{
	ioService.stop();
	ioThread->join();
	delete ioThread;

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

void networkClient::onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd)
{
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
				case player:
					{
						boost::shared_ptr<genericSprite> newSprite(new Player(packet->name));
						sprite.registerSprite(newSprite);
					}
					break;
				case platform:
					{
						boost::shared_ptr<genericSprite> newSprite(new Platform(packet->name));
						sprite.registerSprite(newSprite);
					}
					break;
				case bubble:
					{
						boost::shared_ptr<genericSprite> newSprite(new Bubble(packet->name));
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
					{
						std::cout << "Error: Name already in use" << std::endl;
					}
					break;
				}
				
			}
			break;
		case animationChangePacketID:
			{
				animationChangePacket *packet = (animationChangePacket *)buffer;
				sprite.Sprites[packet->spriteID]->changeAnimation(packet->animationID);
			}
			break;
		case serversListPacketID:
			{
				serversListPacket *packet = (serversListPacket *)buffer;
				for (unsigned short i = 0; i < packet->numServers; ++i){
					fullServerEntry newEntry;
					memcpy((void *)&newEntry.entry, (void *)&packet->serverList[i], sizeof(serverEntry));
					serverList.push_back(newEntry);
				}

			}
			break;
		default:
			std::cout << "Error in client receve packet" << std::endl;
			break;

		}
	}
	socket.async_receive_from(boost::asio::buffer(buffer), receiverEndpoint, boost::bind(&networkClient::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void networkClient::sendKeyPress(sf::Key::Code key, bool down)
{
	if (!inGame){
		return;
	}
	keyPacket packet;
	packet.packetID = keyPacketID;
	packet.down = down;
	if (key == sf::Key::D){
		packet.key = keyRight;
	}else if (key == sf::Key::A){
		packet.key = keyLeft;
	}else if (key == sf::Key::Q){
		packet.key = keyAction;
	}else if (key == sf::Key::W){
		packet.key = keyUp;
	}else if (key == sf::Key::S){
		packet.key = keyDown;
	}else{
		return;
	}

	socket.send_to(boost::asio::buffer((const void *)&packet, 9), receiverEndpoint);
}
