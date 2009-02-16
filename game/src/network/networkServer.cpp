#ifdef SERVER
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "../crc.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
#include <map>
#include <vector>


#include "networkServer.hpp"
#include "packets.hpp"
#include "../sprite/spriteManager.hpp"
#include "../sprite/genericSprite.hpp"
#include "../sprite/player.hpp"
#include "../sprite/platform.hpp"
#include "../sprite/bubble.hpp"

boost::shared_ptr<networkServer> server;

boost::asio::io_service networkServer::ioService;

networkServer::networkServer() 
	:
		serverSocket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 9935)),
		timer(ioService, boost::posix_time::seconds(2))
{
	posUpdate = 0;

	serverSocket.async_receive_from(boost::asio::buffer(buffer), endpoint, boost::bind(&networkServer::onRecivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	timer.async_wait(boost::bind(&networkServer::onSpriteUpdate, this, boost::asio::placeholders::error));
	//thread threads(ioService);
	//boost::thread test(threads);
	{
		boost::shared_ptr<genericSprite> newPlatform(new Platform("platform0"));
		newPlatform->SetY(50);
		sprite.registerSprite(newPlatform);
	}
	{
		boost::shared_ptr<genericSprite> newPlatform(new Platform("platform1"));
		newPlatform->SetY(50);
		newPlatform->SetX(66);
		sprite.registerSprite(newPlatform);
	}
	{
		boost::shared_ptr<genericSprite> newBubble(new Bubble("bubble0"));
		sprite.registerSprite(newBubble);
	}
}

networkServer::~networkServer()
{
}

bool networkServer::runServer()
{
	
	std::cout << "Server Started" << std::endl;
	ioService.run();

	return true;
}

void networkServer::onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd)
{
	if (error){
		//std::cout << error.message() << std::endl;

		if (!(Players.find(endpoint.port()) == Players.end())){

			disconnect(endpoint.port());

		}
	}else{

		if (Players.find(endpoint.port()) != Players.end()){
			Players[endpoint.port()]->timer.expires_from_now(boost::posix_time::seconds(10));
			Players[endpoint.port()]->timer.async_wait(boost::bind(&networkServer::playerInfo::disconnect, Players[endpoint.port()], boost::asio::placeholders::error));
			
		}

		packetIDs packetID;
		memcpy(&packetID, buffer, 4);
		switch(packetID)
		{
		case connectPacketID:
			
			{
				connectPacket *packet = (connectPacket *)buffer;
				CRC crc;

				//boost::crc_16_type  result;
				std::string name = packet->name;//, packet->nameLength);

				int playerID = crc.stringToShort(name);

				if (sprite.Sprites.find(playerID) != sprite.Sprites.end()){
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

				boost::shared_ptr<genericSprite> newPlayer(new Player(packet->name));
				
				sprite.registerSprite(newPlayer);
				player->playerSprite = newPlayer;

				player->timer.async_wait(boost::bind(&networkServer::playerInfo::disconnect, player, boost::asio::placeholders::error));
				
							
				std::cout << "Player " << player->name << " connected from " << player->endpoint.address().to_v4().to_string() << std::endl;
				{
					spriteManager::spriteContainer::iterator iter;
					for(iter = sprite.Sprites.begin(); iter != sprite.Sprites.end(); ++iter){

						spriteCreationPacket packet;
						packet.packetID = spriteCreationPacketID;
						packet.spriteType = iter->second->spriteType;
						packet.nameLength = iter->second->name.length();
						strcpy(packet.name, iter->second->name.c_str());

						serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, 10 + packet.nameLength), player->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
						
					}
				}
				{
					playerContainer::iterator iter;
					for(iter = Players.begin(); iter != Players.end(); ++iter){

						spriteCreationPacket packet;
						packet.packetID = spriteCreationPacketID;
						packet.spriteType = player->playerSprite->spriteType;
						packet.nameLength = player->playerSprite->name.length();
						strcpy(packet.name, player->playerSprite->name.c_str());

						serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, 10 + packet.nameLength), iter->second->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
						
					}
				}
				Players[endpoint.port()] = player;

			
			}
			break;
		case keyPacketID:
			{
				keyPacket *packet = (keyPacket *)buffer;
				if (Players.find(endpoint.port()) == Players.end()){
					break;
				}
				dynamic_cast<Player *>(Players[endpoint.port()]->playerSprite.get())->keyMap[packet->key] = packet->down;
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
		//std::cout << error.message() << std::endl;
	}
}

void networkServer::onSpriteUpdate(const boost::system::error_code& error)
{
	if (error == boost::asio::error::operation_aborted){
		std::cout << "What?" << std::endl;
	}
	sprite.update();
	for(spriteManager::spriteContainer::iterator it = sprite.Sprites.begin(); it != sprite.Sprites.end(); ++it){
		boost::shared_ptr<genericSprite> currentSprite = it->second;
		if (currentSprite->nonNetworked){
			continue;
		}
		sf::Vector2f position = currentSprite->GetPosition();
		if (currentSprite->timesSkiped <= 25){
			if (currentSprite->lastX == position.x && currentSprite->lastY == position.y){
				++currentSprite->timesSkiped;
				continue;
			}
		}
		currentSprite->lastX = position.x;
		currentSprite->lastY = position.y;
		currentSprite->timesSkiped = 0;
		spritePosPacket packet;
		packet.packetID = spritePosPacketID;
		packet.spriteID = it->first;
		
		packet.x = position.x;
		packet.y = position.y;
		packet.flipped = currentSprite->flipped;

		animationChangePacket animationPacket;
		bool useAnimationPacked = false;
		if (currentSprite->lastAnimationName != currentSprite->currentAnimation->name){
			
			animationPacket.packetID = animationChangePacketID;
			animationPacket.spriteID = it->first;
			animationPacket.animationID = CRC().stringToShort(currentSprite->currentAnimation->name);
			currentSprite->lastAnimationName = currentSprite->currentAnimation->name;
			useAnimationPacked = true;
		}
		//boost::asio::ConstBufferSequence handler;
		playerContainer::iterator iter;
		for( iter = Players.begin(); iter != Players.end(); ++iter ) {
			
			//a bit too hackish for my likings
			if (useAnimationPacked){
				serverSocket.async_send_to(boost::asio::buffer((const void *)&animationPacket, sizeof(animationPacket)), iter->second->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
			}
			serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, sizeof(packet)), iter->second->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
	}
	timer.expires_from_now(boost::posix_time::milliseconds(15));
	timer.async_wait(boost::bind(&networkServer::onSpriteUpdate, this, boost::asio::placeholders::error));

}

void networkServer::disconnect(unsigned short playerID)
{
	spriteDeletionPacket packet;
	packet.packetID = spriteDeletionPacketID;
	CRC crc;
	if (Players.find(playerID) == Players.end()){
		std::cout << "Could not find player" << std::endl;
		return;
	}
	packet.spriteID = crc.stringToShort(Players[playerID]->name);
	playerContainer::iterator iter;
	for (iter = Players.begin(); iter != Players.end(); ++iter){
		serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, sizeof(packet)), iter->second->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
	std::cout << "Player " << Players[playerID]->playerSprite->name << " has disconnected." << std::endl;
	Players[playerID]->timer.cancel();
	sprite.removeSprite(packet.spriteID);
	Players.erase(playerID);
	
}

void networkServer::playerInfo::disconnect(const boost::system::error_code& e)
{
	if (e == boost::asio::error::operation_aborted){
		return;
	}
	server->disconnect(endpoint.port());
}

#endif // ifdef SERVER
