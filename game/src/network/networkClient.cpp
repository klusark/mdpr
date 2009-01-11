#include <boost/asio.hpp>
#include <boost/crc.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

//#include <ClanLib/core.h>
//#include <ClanLib/network.h>

#include <iostream>

#include "networkClient.hpp"
#include "packets.hpp"
#include "../sprite/spriteManager.hpp"
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

Network::Client::Client() : socket(ioService)
{
	udp::resolver resolver(ioService);

	udp::resolver::query query(udp::v4(), "24.85.77.75", "5000");
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
		packet.nameLength = 7;
		strcpy(packet.name, "klusars");
		
		
		socket.send_to(boost::asio::buffer((const void *)&packet, 13), receiverEndpoint);
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
	if (packetID == spritePacketID){

	}
	switch(packetID)
	{
	case spritePacketID:
		{
			spritePacket *packet = (spritePacket *)buffer;
			sprite.registerSprite("player", packet->name);
		}
		break;
	case spritePosPacketID:
		{
			spritePosPacket *packet = (spritePosPacket *)buffer;
			boost::mutex::scoped_lock lock(sprite.spriteMutex);
			if (sprite.Sprites.find(packet->spriteID) == sprite.Sprites.end()){
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
	keyPacket packet;
	packet.packetID = keyPacketID;
	packet.down = down;
	packet.key = keyRight;

	socket.send_to(boost::asio::buffer((const void *)&packet, 9), receiverEndpoint);
}
