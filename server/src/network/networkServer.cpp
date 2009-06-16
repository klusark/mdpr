#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "helpers.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include <iostream>
#include <map>
#include <vector>

#include "networkServer.hpp"
#include "network/packets.hpp"
#include "sprite/spriteManager.hpp"
#include "sprite/genericSprite.hpp"
#include "sprite/player.hpp"
#include "sprite/platform.hpp"
#include "sprite/bubble.hpp"

using boost::asio::ip::udp;

boost::shared_ptr<networkServer> server;

networkServer::networkServer() 
	:	serverSocket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 9935)),
		spriteUpdateTimer(ioService, boost::posix_time::seconds(2)),
		masterServerUpdateTimer(ioService, boost::posix_time::seconds(1)),
		removeIdlePlayersTimer(ioService, boost::posix_time::seconds(10))
{
	posUpdate = 0;

	serverSocket.async_receive_from(boost::asio::buffer(buffer), endpoint, boost::bind(&networkServer::onReceivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	packetServerInfo.packetID = serverInfoPacketID;
	packetServerInfo.port = 9935;

	udp::resolver resolver(ioService);
	udp::resolver::query query(udp::v4(), "127.0.0.1", "9937");
	masterServerEndpoint = *resolver.resolve(query);

	spriteUpdateTimer.async_wait(boost::bind(&networkServer::onSpriteUpdate, this, boost::asio::placeholders::error));
	masterServerUpdateTimer.async_wait(boost::bind(&networkServer::updateMasterServer, this, boost::asio::placeholders::error));
	removeIdlePlayersTimer.async_wait(boost::bind(&networkServer::removeIdlePlayers, this, boost::asio::placeholders::error));

	for (short i = 0; i < numIOServiceThreads; ++i){
		ioThreads.create_thread(boost::bind(&networkServer::ioServiceThread, this));
	}

	for (int i = 0; i < 20; ++i){
		std::string name = "platform";
		char buff[4];
		sprintf(buff, "%d", i);
		name += buff;
		boost::shared_ptr<genericSprite> newPlatform(new Platform(name));
		newPlatform->SetY(100);
		newPlatform->SetX(i*16);
		sprite.registerSprite(newPlatform);
	}

	{
	//	boost::shared_ptr<genericSprite> newBubble(new Bubble("bubble0"));
	//	sprite.registerSprite(newBubble);
	}
}

networkServer::~networkServer()
{
}

void networkServer::runServer()
{
	
	std::cout << "Server Started" << std::endl;
	ioThreads.join_all();

}

void networkServer::onReceivePacket(const boost::system::error_code& error, size_t bytesRecvd)
{
	if (error){
		//std::cout << "onReceivePacket: " << error.message() << std::endl;

		if (!(Players.find(endpoint.port()) == Players.end())){

			disconnect(endpoint.port());

		}
	}else{
		if (Players.find(endpoint.port()) != Players.end()){
			Players[endpoint.port()]->stillAlive = true;
		}

		packetIDs packetID;
		memcpy(&packetID, buffer, 4);
		switch(packetID)
		{
		case connectPacketID:
			
			{
				connectPacket *packet = (connectPacket *)buffer;

				std::string name = packet->name;//, packet->nameLength);

				int playerID = stringToCRC(name);

				if (sprite.Sprites.find(playerID) != sprite.Sprites.end()){
					//Player with the same name is already in the game
					errorPacket packet;
					packet.packetID = errorPacketID;
					packet.errorID = nameInUse;
					serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, 8), endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
					break;
				}

				{
					//Sends the connection accepted packet to tell the client that they have succesfuly joined the server.
					connectionAcceptedPacket packet;
					packet.packetID = connectionAcceptedPacketID;
					serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, sizeof(packet)), endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
				}

				boost::shared_ptr<playerInfo> player(new playerInfo);
				player->endpoint = endpoint;
				player->name = packet->name;

				boost::shared_ptr<genericSprite> newPlayer(new Player(packet->name));
				
				sprite.registerSprite(newPlayer);
				player->playerSprite = newPlayer;

				{
					//Send all the sprite types to the client
					spriteManager::spriteTypeContainer::iterator iter;
					for(iter = sprite.SpriteTypes.begin(); iter != sprite.SpriteTypes.end(); ++iter){

						spriteTypeCreationPacket packet;
						packet.packetID = spriteTypeCreationPacketID;
						packet.spriteTypeID = iter->first;
						packet.fileNameLength = iter->second.length();
						strcpy(packet.fileName, iter->second.c_str());

						serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, sizeof(spriteTypeCreationPacket) - 255 + packet.fileNameLength), player->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
						
					}
				}

				{
					//Send all the animations to the client
					spriteManager::animationPacketContainer::iterator iter;
					for(iter = sprite.Animations.begin(); iter != sprite.Animations.end(); ++iter){

						serverSocket.async_send_to(boost::asio::buffer((const void *)&iter->second, sizeof(animationCreationPacket)), player->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
						
					}
				}
				
				{
					//Send all the sprites to the client
					spriteManager::spriteContainer::iterator iter;
					for(iter = sprite.Sprites.begin(); iter != sprite.Sprites.end(); ++iter){

						spriteCreationPacket packet;
						packet.packetID = spriteCreationPacketID;
						packet.spriteType = stringToCRC(iter->second->spriteTypeName);
						packet.nameLength = iter->second->name.length();
						strcpy(packet.name, iter->second->name.c_str());

						serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, sizeof(spriteCreationPacket) - 255 + packet.nameLength), player->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
						
					}
				}

				{
					//Sends the current animation of all the sprites to the new player
					spriteManager::spriteContainer::iterator iter;
					for(iter = sprite.Sprites.begin(); iter != sprite.Sprites.end(); ++iter){
						animationChangePacket packet;
						packet.packetID = animationChangePacketID;
						packet.spriteID = iter->first;
						packet.animationID = iter->second->currentAnimation->CRCName;

						serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, sizeof(animationChangePacket)), player->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
						
					}
				}

				{
					//Send the new player to all the already connected players
					playerContainer::iterator iter;
					for(iter = Players.begin(); iter != Players.end(); ++iter){

						spriteCreationPacket packet;
						packet.packetID = spriteCreationPacketID;
						packet.spriteType = player->playerSprite->spriteType;
						packet.spriteType = stringToCRC(player->playerSprite->spriteTypeName);
						packet.nameLength = player->playerSprite->name.length();
						strcpy(packet.name, player->playerSprite->name.c_str());

						serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, sizeof(spriteCreationPacket) - 255 + packet.nameLength), iter->second->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
						
					}
				}

				Players[endpoint.port()] = player;
				std::cout << "Player " << player->name << " connected from " << player->endpoint.address().to_v4().to_string() << std::endl;

				{
					//Send the done connecting packet to tell the client that all the info has been sent
					doneConnectingPacket packet;
					packet.packetID = doneConnectingPacketID;

					serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, 4), player->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
				}			
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
		case getFullServerInfoPacketID:
			{
				//getFullServerInfoPacket *packet = (getFullServerInfoPacket *)buffer;
				fullServerInfoPacket packet;
				packet.packetID = fullServerInfoPacketID;

				serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, sizeof(fullServerInfoPacket)), endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
			}
			break;
		default:
			std::cout << "Error in packed recved." << std::endl;
			break;

		}
	}
	serverSocket.async_receive_from(boost::asio::buffer(buffer), endpoint, boost::bind(&networkServer::onReceivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	
}

void networkServer::handleSendTo(const boost::system::error_code& error, size_t bytes_sent)
{
	if (error){
		std::cout << "handleSendTo: " <<  error.message() << std::endl;
		return;
	}
}

void networkServer::removeIdlePlayers(const boost::system::error_code& error)
{
	//boost::mutex::scoped_lock lock(PlayerMutex);
	for (networkServer::playerContainer::iterator it = Players.begin(); it != Players.end(); ++it){
		if (!it->second->stillAlive){
			disconnect(stringToCRC(it->second->name));
			break;
		}else{
			it->second->stillAlive = false;
		}
	}
	removeIdlePlayersTimer.expires_from_now(boost::posix_time::seconds(10));
	removeIdlePlayersTimer.async_wait(boost::bind(&networkServer::removeIdlePlayers, this, boost::asio::placeholders::error));
}

void networkServer::onSpriteUpdate(const boost::system::error_code& error)
{
	if (error){
		std::cout << "onSpriteUpdate: " << error.message() << std::endl;
		return;
	}
	boost::mutex::scoped_lock lock(sprite.spriteMutex);
	sprite.update();
	for(spriteManager::spriteContainer::iterator it = sprite.Sprites.begin(); it != sprite.Sprites.end(); ++it){
		boost::shared_ptr<genericSprite> currentSprite = it->second;
		if (currentSprite->nonNetworked){
			continue;
		}
		Position position = currentSprite->GetPosition();
		if (currentSprite->timesSkiped <= 100){
			if ((floor(currentSprite->lastX) == floor(position.x)) && (floor(currentSprite->lastY) == floor(position.y)) && (currentSprite->lastAnimationName == currentSprite->currentAnimation->name) && (currentSprite->lastFrame == currentSprite->currentAnimation->currentFrame)){
				++currentSprite->timesSkiped;
				continue;
			}
		}
		currentSprite->lastFrame = currentSprite->currentAnimation->currentFrame;
		currentSprite->lastX = position.x;
		currentSprite->lastY = position.y;
		currentSprite->timesSkiped = 0;

		positionAndFrameUpdatePacket packet;
		packet.packetID = positionAndFrameUpdatePacketID;
		packet.spriteID = it->first;
		
		packet.x = position.x;
		packet.y = position.y;
		packet.flipped = currentSprite->flipped;
		packet.currentFrame = currentSprite->currentAnimation->currentFrame;

		animationChangePacket animationPacket;
		bool useChangePacket = false;
		if (currentSprite->lastAnimationName != currentSprite->currentAnimation->name){

			animationPacket.packetID = animationChangePacketID;
			animationPacket.spriteID = it->first;
			animationPacket.animationID = currentSprite->currentAnimation->CRCName;

			currentSprite->lastAnimationName = currentSprite->currentAnimation->name;
			useChangePacket = true;
		}

		playerContainer::iterator iter;
		for( iter = Players.begin(); iter != Players.end(); ++iter ) {
			if(useChangePacket){
				serverSocket.async_send_to(boost::asio::buffer((const void *)&animationPacket, sizeof(animationPacket)), iter->second->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
			}
			serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, sizeof(packet)), iter->second->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
	}
	spriteUpdateTimer.expires_from_now(boost::posix_time::milliseconds(20));
	spriteUpdateTimer.async_wait(boost::bind(&networkServer::onSpriteUpdate, this, boost::asio::placeholders::error));

}

void networkServer::updateMasterServer(const boost::system::error_code& error)
{
	if (error){
		std::cout << "updateMasterServer: " << error.message() << std::endl;
		return;
	}

	serverSocket.send_to(boost::asio::buffer((const void *)&packetServerInfo, 6), masterServerEndpoint);

	masterServerUpdateTimer.expires_from_now(boost::posix_time::seconds(15));
	masterServerUpdateTimer.async_wait(boost::bind(&networkServer::updateMasterServer, this, boost::asio::placeholders::error));
}

void networkServer::disconnect(unsigned short playerID)
{
	spriteDeletionPacket packet;
	packet.packetID = spriteDeletionPacketID;
	if (Players.find(playerID) == Players.end()){
		std::cout << "Could not find player" << std::endl;
		return;
	}
	packet.spriteID = stringToCRC(Players[playerID]->name);
	playerContainer::iterator iter;
	for (iter = Players.begin(); iter != Players.end(); ++iter){
		serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, sizeof(packet)), iter->second->endpoint, boost::bind(&networkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
	std::cout << "Player " << Players[playerID]->playerSprite->name << " has disconnected." << std::endl;
	//Players[playerID]->timer.cancel();
	sprite.removeSprite(packet.spriteID);
	Players.erase(playerID);
	
}

void networkServer::playerInfo::disconnect(const boost::system::error_code& error)
{
	if (error){
		std::cout << "disconnect: " << error.message() << std::endl;
		return;
	}
	server->disconnect(endpoint.port());
}

void networkServer::ioServiceThread()
{
	try{
		ioService.run();
	}catch (std::exception& e){
		std::cout << "Exception: " << e.what() << std::endl;
	}catch(...){
		std::cout << "Unknown Exception caught" << std::endl; 
	}
}
