#ifdef SERVER
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/crc.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
//#include <boost/thread.hpp>

#include <iostream>
#include <map>
#include <vector>


#include "networkServer.hpp"
#include "packets.hpp"
#include "../sprite/spriteManager.hpp"
#include "../sprite/genericSprite.hpp"
#include "../sprite/player.hpp"
#include "../sprite/platform.hpp"

boost::asio::io_service networkServer::ioService;

struct thread
{
public:
	thread(boost::asio::io_service &ioService) 
		: ioService(ioService)
	{}
	void operator()(){
		
		for (;;){
			try {
				ioService.run();
			}catch(std::exception& e){
				std::cout << "Exception: " << e.what() << "\n";
			}
		}
		return;
	}
private:
	boost::asio::io_service& ioService;
};

networkServer::networkServer() 
	:
		serverSocket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 9935)),
		timer(ioService, boost::posix_time::seconds(2))
{
	boost::shared_ptr<spriteManager> tmpSprite(new spriteManager(true));
	ServerSpriteManager = tmpSprite;
	posUpdate = 0;

	serverSocket.async_receive_from(boost::asio::buffer(buffer), endpoint, boost::bind(&networkServer::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	timer.async_wait(boost::bind(&networkServer::onSpriteUpdate, this, boost::asio::placeholders::error));
	//thread threads(ioService);
	//boost::thread test(threads);
	boost::shared_ptr<genericSprite> platform(new Platform("platform0"));
	ServerSpriteManager->registerSprite(platform);
#ifdef SERVER
	ioService.run();
#endif

}

networkServer::~networkServer()
{
}

bool networkServer::runServer()
{

	std::cout << "Server Started" << std::endl;


	return true;
}

void networkServer::onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd)
{
	if (error){
		std::cout<<error.message()<<std::endl;

		if (Players.find(endpoint.port()) == Players.end()){
			return;
		}
		boost::crc_16_type  result;
		std::string name = Players.find(endpoint.port())->second->name;
		result.process_bytes(name.c_str(), name.length());
		std::stringstream buf;
		buf << result.checksum();
		int playerID = atoi(buf.str().c_str());
		ServerSpriteManager->Sprites.erase(ServerSpriteManager->Sprites.find(playerID));
		//Players.find(endpoint.port())->second->name;
		

		Players.erase(Players.find(endpoint.port()));

		std::cout<<error.message()<<std::endl;
	}else{

		if (Players.find(endpoint.port()) != Players.end()){
			Players[endpoint.port()]->timer.expires_from_now(boost::posix_time::seconds(20));
			Players[endpoint.port()]->timer.async_wait(boost::bind(&networkServer::playerInfo::disconnect, Players[endpoint.port()], boost::asio::placeholders::error));
			
		}

		packetIDs packetID;
		memcpy(&packetID, buffer, 4);
		switch(packetID)
		{
		case connectPacketID:
			
			{
				connectPacket *packet = (connectPacket *)buffer;

				boost::crc_16_type  result;
				result.process_bytes(packet->name, packet->nameLength);
				std::stringstream buf;
				buf << result.checksum();
				int playerID = atoi(buf.str().c_str());

				if (ServerSpriteManager->Sprites.find(playerID) != ServerSpriteManager->Sprites.end()){
					//Player with the same name is already in the game
					errorPacket packet;
					packet.packetID = errorPacketID;
					packet.errorID = nameInUse;
					serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, 8), endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
					return;
				}

				boost::shared_ptr<playerInfo> player(new playerInfo);
				player->endpoint = endpoint;
				player->name = packet->name;
				
				ServerSpriteManager->registerSprite("player", player->name);
				player->sprite = ServerSpriteManager->Sprites[playerID];
				//player->timer.expires_from_now(boost::posix_time::seconds(20));
				player->timer.async_wait(boost::bind(&networkServer::playerInfo::disconnect, player, boost::asio::placeholders::error));
				
				
				
				std::cout << "Player " << player->name << " connected from " << player->endpoint.address().to_v4().to_string() << std::endl;
				{
					spriteManager::spriteContainer::iterator iter;
					for(iter = ServerSpriteManager->Sprites.begin(); iter != ServerSpriteManager->Sprites.end(); ++iter){

						spritePacket packet;
						packet.packetID = spritePacketID;
						packet.nameLength = iter->second->name.length();
						strcpy(packet.name, iter->second->name.c_str());

						serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, 6 + packet.nameLength), player->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
						
					}
				}
				{
					playerContainer::iterator iter;
					for(iter = Players.begin(); iter != Players.end(); ++iter){

						spritePacket packet;
						packet.packetID = spritePacketID;
						packet.nameLength = player->sprite->name.length();
						strcpy(packet.name, player->sprite->name.c_str());

						serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, 6 + packet.nameLength), iter->second->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
						
					}
				}
				Players[endpoint.port()] = player;

			
			}
			break;
		case keyPacketID:
			{
				keyPacket *packet = (keyPacket *)buffer;
				if (Players.find(endpoint.port()) == Players.end()){
					return;
				}
				dynamic_cast<Player *>(Players[endpoint.port()]->sprite.get())->keyMap[packet->key] = packet->down;

				/*if (packet->down){
					float velocity = (-1*(packet->key == keyLeft)+(packet->key == keyRight))*60;
					Players.find(endpoint.port())->second->sprite->setXVelocity(velocity);//->SetX(50);
				}else{
					Players.find(endpoint.port())->second->sprite->setXVelocity(0);//SetX(100);
				}*/
			}
			break;
		default:
			std::cout << "Error in packed recved." << std::endl;
			break;

		}
	}
	serverSocket.async_receive_from(boost::asio::buffer(buffer), endpoint, boost::bind(&networkServer::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	
}

void networkServer::handleSendTo(const boost::system::error_code& error, size_t bytes_sent)
{
	if (error){
		std::cout<<error.message()<<std::endl;
	}
}

void networkServer::onSpriteUpdate(const boost::system::error_code& error)
{
	if (error == boost::asio::error::operation_aborted){
		std::cout<<"What?";
	}
	ServerSpriteManager->update();
	for(spriteManager::spriteContainer::iterator it = ServerSpriteManager->Sprites.begin(); it != ServerSpriteManager->Sprites.end(); ++it){
		boost::shared_ptr<genericSprite> currentSprite = it->second;

		spritePosPacket packet;
		packet.packetID = spritePosPacketID;
		packet.spriteID = it->first;
		sf::Vector2f position = currentSprite->GetPosition();
		packet.x = position.x+50;
		packet.y = position.y+50;

		playerContainer::iterator iter;
		for( iter = Players.begin(); iter != Players.end(); ++iter ) {
			serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, sizeof(packet)), iter->second->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
	}
	timer.expires_from_now(boost::posix_time::milliseconds(15));
	timer.async_wait(boost::bind(&networkServer::onSpriteUpdate, this, boost::asio::placeholders::error));

}

void networkServer::playerInfo::disconnect(const boost::system::error_code& e)
{
	if (e == boost::asio::error::operation_aborted){
		return;
	}
	std::cout<<"asdfasfasfasdfasdf";

}

#endif //ifdef SERVER
