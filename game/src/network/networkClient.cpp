#include <boost/asio.hpp>
#include <boost/crc.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>



#include <iostream>

#include "../MDPRGame.hpp"
#include "networkClient.hpp"
#include "packets.hpp"
#include "../sprite/spriteManager.hpp"
#include "../sprite/player.hpp"
#include "../sprite/platform.hpp"

using boost::asio::ip::udp;
struct thread
{
public:
	thread(boost::asio::io_service &ioService) 
		: ioService(ioService)
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

Network::Client::Client()
	:	socket(ioService),
		inGame(true)
{
	udp::resolver resolver(ioService);

	udp::resolver::query query(udp::v4(), MDPR.serverIP, MDPR.serverPort);
	udp::resolver::iterator iterator = resolver.resolve(query);

	receiverEndpoint = *resolver.resolve(query);
	socket.open(udp::v4());

	socket.async_receive_from(boost::asio::buffer(buffer), receiverEndpoint, boost::bind(&Network::Client::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	thread threads(ioService);
	ioThread = new boost::thread(threads);


}

Network::Client::~Client()
{
	ioService.stop();
	ioThread->join();
	delete ioThread;

}

bool Network::Client::run()
{
	try
	{
		connectPacket packet;
		packet.packetID = connectPacketID;
		packet.nameLength = MDPR.playerName.length();
		strcpy(packet.name, MDPR.playerName.c_str());
		
		
		socket.send_to(boost::asio::buffer((const void *)&packet, 6 + packet.nameLength), receiverEndpoint);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
		return false;
	}
	return true;
}

void Network::Client::onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd)
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
	default:
		std::cout << "Error in client receve packet" << std::endl;
		break;

	}
	}
	socket.async_receive_from(boost::asio::buffer(buffer), receiverEndpoint, boost::bind(&Network::Client::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Network::Client::sendKeyPress(sf::Key::Code key, bool down)
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
	}else{
		return;
	}

	socket.send_to(boost::asio::buffer((const void *)&packet, 9), receiverEndpoint);
}
