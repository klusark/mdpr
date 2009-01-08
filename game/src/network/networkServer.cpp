#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/crc.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include <iostream>
#include <map>
#include <vector>

#include "network.hpp"
#include "networkServer.hpp"
#include "packets.hpp"
#include "../sprite/spriteManager.hpp"
#include "../sprite/genericSprite.hpp"

struct thread
{
public:
	thread(boost::asio::io_service &ioService) 
		: ioService(ioService)
	{}
	void operator()(){
		
		for (;;){
			ioService.run();
		}
		return;
	}
private:
	boost::asio::io_service& ioService;
};

Network::Server::Server() 
	:
		serverSocket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 5000)),
		timer(ioService, boost::posix_time::seconds(2))
{
	boost::shared_ptr<spriteManager> tmpSprite(new spriteManager(true));
	ServerSpriteManager = tmpSprite;
	posUpdate = 0;

	serverSocket.async_receive_from(boost::asio::buffer(buffer), endpoint, boost::bind(&Network::Server::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	timer.async_wait(boost::bind(&Network::Server::onSpriteUpdate, this, boost::asio::placeholders::error));
	thread threads(ioService);
	boost::thread test(threads);
#ifdef SERVER
	test.join();
#endif

}

Network::Server::~Server()
{
}

bool Network::Server::runServer()
{

	std::cout << "Server Started" << std::endl;


	return true;
}

void Network::Server::onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd)
{
	serverSocket.async_receive_from(boost::asio::buffer(buffer), endpoint, boost::bind(&Network::Server::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	
	

	packetIDs packetID;
	memcpy(&packetID, buffer, 4);
	switch(packetID)
	{
	case connectPacketID:
		
		{
			connectPacket *packet = (connectPacket *)buffer;
			boost::shared_ptr<playerInfo> player(new playerInfo);
			player->endpoint = endpoint;
			player->name = packet->name;

			boost::crc_16_type  result;
			result.process_bytes(packet->name, packet->nameLength);
			std::stringstream buf;
			buf << result.checksum();
			
			ServerSpriteManager->registerSprite("player", player->name);
			player->sprite = ServerSpriteManager->Sprites[atoi(buf.str().c_str())];
			Players.push_back(player);
			std::cout << "Player " << player->name << " connected from " << player->endpoint.address().to_string() << std::endl;

			spriteManager::spriteContainer::iterator iter;
			for(iter = ServerSpriteManager->Sprites.begin(); iter != ServerSpriteManager->Sprites.end(); ++iter){
				//boost::shared_ptr<genericSprite> tempSprite = iter->second;

				spritePacket packet;
				packet.packetID = spritePacketID;
				packet.nameLength = iter->second->name.length();
				strcpy(packet.name, iter->second->name.c_str());

				serverSocket.send_to(boost::asio::buffer((const void *)&packet, 6 + packet.nameLength), player->endpoint);
				
			}

		
		}
		break;
	default:
		std::cout << "error";
		break;

	}

	
	
}


void Network::Server::onSpriteUpdate(const boost::system::error_code& error)
{
	
	ServerSpriteManager->update();
	for(spriteManager::spriteContainer::iterator it = ServerSpriteManager->Sprites.begin(); it != ServerSpriteManager->Sprites.end(); ++it){
		boost::shared_ptr<genericSprite> currentSprite = it->second;

		spritePosPacket packet;
		packet.packetID = spritePosPacketID;
		packet.spriteID = it->first;
		sf::Vector2f position = currentSprite->GetPosition();
		packet.x = position.x+50;
		packet.y = position.y+50;

		for (unsigned short i = 0; i < Players.size(); ++i){
			serverSocket.send_to(boost::asio::buffer((const void *)&packet, sizeof(packet)), Players[i]->endpoint);
		}

		/*//if (posUpdate == 4){
			spritePosPacket packet;

			spriteUpdatePosPacket.output.write_string(currentSprite->name);
			spriteUpdatePosPacket.output.write_float32(currentSprite->getX());//x
			spriteUpdatePosPacket.output.write_float32(currentSprite->getY());//y

			//netsession->get_all().send("spriteUpdatePos", spriteUpdatePosPacket);
			//posUpdate = 0;
		//}
*/
		/*CL_NetPacket spriteUpdateAccelPacket;

		spriteUpdateAccelPacket.output.write_string(currentSprite->name);
		spriteUpdateAccelPacket.output.write_float32(currentSprite->getXAccel());//x
		spriteUpdateAccelPacket.output.write_float32(currentSprite->getYAccel());//y

		netsession->get_all().send("spriteUpdateAccel", spriteUpdateAccelPacket);


		CL_NetPacket spriteUpdateVelocityPacket;

		spriteUpdateVelocityPacket.output.write_string(currentSprite->name);
		spriteUpdateVelocityPacket.output.write_float32(10.0f);//x
		spriteUpdateVelocityPacket.output.write_float32(100.0f);//y

		netsession->get_all().send("spriteUpdateVelocity", spriteUpdateVelocityPacket);*/

	}
	//++posUpdate;
	
	//std::cout<<"asdfasdfas "<<std::endl;
	timer.expires_from_now(boost::posix_time::seconds(2));
	timer.async_wait(boost::bind(&Network::Server::onSpriteUpdate, this, boost::asio::placeholders::error));

}

/*void Network::Server::onReciveConnect(CL_NetPacket &packet, CL_NetComputer &computer)
{
	std::string name = packet.input.read_string();
	std::cout << "asdf" << std::endl;
	sprite->registerSprite("player", name);
	CL_NetPacket spritePacket;
	spritePacket.output.write_string(name);
	spritePacket.output.write_string("player");
	computer.send("sprite", spritePacket);
}


void Network::Server::onDisconnect(CL_NetComputer &computer)
{
	std::cout << "Client disconnected." << std::endl;
}
*/
