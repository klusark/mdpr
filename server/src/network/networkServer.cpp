#include "helpers.hpp"
#include <Poco/SharedPtr.h>
#include <Poco/NObserver.h>
#include <Poco/Thread.h>
#include <Poco/Net/NetException.h>
#include <Poco/ScopedLock.h>

#include <map>
#include <vector>
#include <cmath>

#include "networkServer.hpp"
#include "network/packets.hpp"
#include "sprite/spriteManager.hpp"
#include "sprite/genericSprite.hpp"
#include "sprite/player.hpp"
#include "sprite/platform.hpp"
#include "sprite/bubble.hpp"

POCO_SERVER_MAIN(NetworkServer)

Poco::SharedPtr<NetworkServer> server;

NetworkServer::NetworkServer() 
	:	buffer(new char[BUFFER_SIZE]),
		spriteUpdateTimer(250, 5),
		masterServerUpdateTimer(200, 20000),
		removeIdlePlayersTimer(10000, 10000)
{
	posUpdate = 0;

	for (int i = 0; i < 25; ++i){
		std::string name = "platform";
		char buff[4];
		sprintf(buff, "%d", i);
		name += buff;
		Poco::SharedPtr<genericSprite> newPlatform(new Platform(name));
		newPlatform->SetY(100);
		newPlatform->SetX((float)50 + (i*16));
		sprite.registerSprite(newPlatform);
	}

	{
	//	Poco::SharedPtr<genericSprite> newBubble(new Bubble("bubble0"));
	//	sprite.registerSprite(newBubble);
	}
}

NetworkServer::~NetworkServer()
{
}

void NetworkServer::initialize(Poco::Util::Application& self)
{
	loadConfiguration(); // load default configuration files, if present
	Poco::Util::ServerApplication::initialize(self);
	logger().information("starting up");
}

int NetworkServer::main(const std::vector<std::string>& args)
{
	// get parameters from configuration file
	if (!config().hasProperty("Server.port")){
		logger().warning("Server.port has not been set. Defaulting to 9935");
		config().setInt("Server.port", 9935);
	}

	if (config().getInt("Server.port") < 1024){
		logger().error("Server.port is below 1024");
		return Application::EXIT_CONFIG;
	}

	if (!config().hasProperty("Server.name")){
		logger().warning("Server.name is not set. Defaulting to 'Unnamed Server'");
		config().setString("Server.name", "Unnamed Server");
	}

	if (!config().hasProperty("Server.MaxPlayers")){
		logger().warning("Server.MaxPlayers is not set. Defaulting to 16");
		config().setInt("Server.MaxPlayers", 16);
	}

	if (!config().hasProperty("Server.Master.updateToMaster") || !config().getBool("Server.Master.updateToMaster", false)){
		logger().information("Server.Master.updateToMaster is not set. Master Server updating is off");
		config().setBool("Server.Master.updateToMaster", false);
	}else{
		if (!config().hasProperty("Server.Master.ip")){
			logger().warning("Server.Master.ip is not set. Defaulting to klusark.ath.cx");
			config().setString("Server.Master.ip", "klusark.ath.cx");
		}
		if (!config().hasProperty("Server.Master.port")){
			logger().warning("Server.Master.port is not set. Defaulting to 9937");
			config().setInt("Server.Master.port", 9937);
		}
	}

	packetServerInfo.packetID = serverInfoPacketID;
	packetServerInfo.port = config().getInt("Server.port");

	Poco::Net::SocketAddress socketAddress("0.0.0.0", config().getInt("Server.port"));
	// set-up a server socke
	socket.bind(socketAddress, true);
	// set-up a SocketReactor...
	Poco::Net::SocketReactor reactor;
	reactor.addEventHandler(socket, Poco::NObserver<NetworkServer, Poco::Net::ReadableNotification>	(*this, &NetworkServer::onReceivePacket));
	reactor.addEventHandler(socket, Poco::NObserver<NetworkServer, Poco::Net::ErrorNotification>	(*this, &NetworkServer::onError));
	// run the reactor in its own thread so that we can wait for
	// a termination request
	
	spriteUpdateTimer.start(Poco::TimerCallback<NetworkServer>(*this, &NetworkServer::spriteUpdate));
	removeIdlePlayersTimer.start(Poco::TimerCallback<NetworkServer>(*this, &NetworkServer::removeIdlePlayers));
	

	Poco::Thread thread;
	thread.start(reactor);
	if (config().getBool("Server.Master.updateToMaster")){
		masterServerUpdateTimer.start(Poco::TimerCallback<NetworkServer>(*this, &NetworkServer::masterServerUpdate));
		unsigned short masterServerPort = (unsigned short)config().getInt("Server.Master.port");
		std::string masterServerIP = config().getString("Server.Master.ip");
		if (masterServerIP.length() != 0){
			masterServerAddress = Poco::Net::SocketAddress(masterServerIP, masterServerPort);
		}
	}
	// wait for CTRL-C or kill
	waitForTerminationRequest();
	// Stop the SocketReactor
	reactor.stop();
	thread.join();

	return Application::EXIT_OK;
}

void NetworkServer::onError(const Poco::AutoPtr<Poco::Net::ErrorNotification>& pNf)
{
	logger().error("OMGWTFBBQ");
}

void NetworkServer::onReceivePacket(const Poco::AutoPtr<Poco::Net::ReadableNotification>& pNf)
{
	Poco::Net::SocketAddress socketAddress;
	int bytesReceived;
	
	try{
		bytesReceived = socket.receiveFrom(buffer, BUFFER_SIZE, socketAddress);
		if (Players.find(socketAddress.port()) != Players.end()){
			Players[socketAddress.port()]->stillAlive = true;
		}

		packetIDs packetID;
		memcpy(&packetID, buffer, 4);
		switch(packetID)
		{
		case connectPacketID:
			
			{
				
				//boost::mutex::scoped_lock lock(sprite.spriteMutex);
				connectPacket *packet = (connectPacket *)buffer;
				if (bytesReceived != sizeof(connectPacket) - 255 + packet->nameLength){
					return;
				}
				if (packet->nameLength == 0){
					return;
				}

				std::string name(packet->name, packet->nameLength);

				int playerID = stringToCRC(name);

				if (sprite.Sprites.find(playerID) != sprite.Sprites.end()){
					//Player with the same name is already in the game
					errorPacket packet;
					packet.packetID = errorPacketID;
					packet.errorID = nameInUse;
					socket.sendTo((const void *)&packet, 8, socketAddress);
					break;
				}

				{
					//Sends the connection accepted packet to tell the client that they have succesfuly joined the server.
					connectionAcceptedPacket packet;
					packet.packetID = connectionAcceptedPacketID;
					socket.sendTo((const void *)&packet, sizeof(connectionAcceptedPacket), socketAddress);
				}

				Poco::SharedPtr<playerInfo> player(new playerInfo);
				player->address = socketAddress;
				player->name = name;

				Poco::SharedPtr<genericSprite> newPlayer(new Player(name));
				
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
						socket.sendTo((const void *)&packet, sizeof(spriteTypeCreationPacket) - 255 + packet.fileNameLength, player->address);
					}
				}

				{
					//Send all the animations to the client
					spriteManager::animationPacketContainer::iterator iter;
					for(iter = sprite.Animations.begin(); iter != sprite.Animations.end(); ++iter){
						socket.sendTo((const void *)&iter->second, sizeof(animationCreationPacket), player->address);
						
					}
				}
				
				{
					//Send all the sprites to the client
					spriteManager::spriteContainer::iterator iter;
					for(iter = sprite.Sprites.begin(); iter != sprite.Sprites.end(); ++iter){
						if(iter->second->nonNetworked){
							continue;
						}

						spriteCreationPacket packet;
						packet.packetID = spriteCreationPacketID;
						packet.spriteType = stringToCRC(iter->second->spriteTypeName);
						packet.nameLength = iter->second->name.length();
						strcpy(packet.name, iter->second->name.c_str());

						positionAndFrameUpdatePacket POSpacket;
						POSpacket.packetID = positionAndFrameUpdatePacketID;
						Position position = iter->second->GetPosition();
						POSpacket.spriteID = iter->first;

						POSpacket.x = position.x;
						POSpacket.y = position.y;
						POSpacket.flipped = iter->second->flipped;
						POSpacket.currentFrame = iter->second->currentAnimation->currentFrame;

						animationChangePacket AnimPacket;
						AnimPacket.packetID = animationChangePacketID;
						AnimPacket.spriteID = iter->first;
						AnimPacket.animationID = iter->second->currentAnimation->CRCName;


						socket.sendTo((const void *)&packet, sizeof(spriteCreationPacket) + packet.nameLength - 255, player->address);
						socket.sendTo((const void *)&POSpacket, sizeof(positionAndFrameUpdatePacket), player->address);
						socket.sendTo((const void *)&AnimPacket, sizeof(animationChangePacket), player->address);
						
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
						socket.sendTo((const void *)&packet, sizeof(spriteCreationPacket) - 255 + packet.nameLength, iter->second->address);
					
					}
				}

				Players[socketAddress.port()] = player;
				logger().information("Player " + player->name + " connected from " + player->address.toString());

				{
					//Send the done connecting packet to tell the client that all the info has been sent
					doneConnectingPacket packet;
					packet.packetID = doneConnectingPacketID;
					socket.sendTo((const void *)&packet, 4, player->address);
				}			
			}
			break;
		case keyPacketID:
			{
				keyPacket *packet = (keyPacket *)buffer;
				if (Players.find(socketAddress.port()) == Players.end()){
					break;
				}
				dynamic_cast<Player *>(Players[socketAddress.port()]->playerSprite.get())->keyMap[packet->key] = packet->down;
				dynamic_cast<Player *>(Players[socketAddress.port()]->playerSprite.get())->keyMapTwo[packet->key] = packet->down;
			}
			break;
		case getFullServerInfoPacketID:
			{
				//getFullServerInfoPacket *packet = (getFullServerInfoPacket *)buffer;
				fullServerInfoPacket packet;
				packet.packetID = fullServerInfoPacketID;
				packet.numPlayers = 4;
				packet.maxPlayers = config().getInt("Server.MaxPlayers");
				std::string serverName = config().getString("Server.name");
				strcpy(packet.serverName, serverName.c_str());
				packet.port = config().getInt("Server.port");

				socket.sendTo((const void *)&packet, sizeof(fullServerInfoPacket) - 256 + serverName.length(), socketAddress);
			}
			break;
		default:
			logger().warning("Unknown packet received");
			break;

		}
	}catch (Poco::Net::ConnectionResetException&){
		unsigned short port = socketAddress.port();
		if (!(Players.find(port) == Players.end())){
		
			disconnect(port);

		}
	}catch (Poco::Exception& e){
		std::string message = "Poco::Exception: "; 
		message += e.what();
		logger().error(message);
	}catch (std::exception& e){
		std::string message = "std::exception: "; 
		message += e.what();
		logger().error(message);
	}
}


void NetworkServer::removeIdlePlayers(Poco::Timer& timer)
{
	for (NetworkServer::playerContainer::iterator it = Players.begin(); it != Players.end(); ++it){
		if (!it->second->stillAlive){
			disconnect(it->first);
			break;
		}else{
			it->second->stillAlive = false;
		}
	}
}


void NetworkServer::spriteUpdate(Poco::Timer& timer)
{
	/*if (error){
		std::cout << "spriteUpdate: " << error.message() << std::endl;
		return;
	}*/
	try{
		Poco::ScopedLock<Poco::Mutex>(sprite.spriteMutex);
		sprite.update();
		for(spriteManager::spriteContainer::iterator it = sprite.Sprites.begin(); it != sprite.Sprites.end(); ++it){
			Poco::SharedPtr<genericSprite> currentSprite = it->second;
			if (currentSprite->nonNetworked){
				continue;
			}
			Position position = currentSprite->GetPosition();
			//1000 is an arbitrary number that should be put into a variable
			if (currentSprite->timesSkiped <= 1000){
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
					socket.sendTo((const void *)&animationPacket, sizeof(animationPacket), iter->second->address);
					
				}
				socket.sendTo((const void *)&packet, sizeof(positionAndFrameUpdatePacket), iter->second->address);
			}
		}
	}catch (Poco::Exception& e){
		std::string message = "Poco::Exception: "; 
		message += e.what();
		logger().error(message);
	}catch (std::exception& e){
		std::string message = "std::exception: "; 
		message += e.what();
		logger().error(message);
	}
}

void NetworkServer::masterServerUpdate(Poco::Timer& timer)
{
	//Updates the master server. 
	socket.sendTo((const void *)&packetServerInfo, sizeof(serverInfoPacket), masterServerAddress);
}

void NetworkServer::disconnect(unsigned short playerID)
{
	spriteDeletionPacket packet;
	packet.packetID = spriteDeletionPacketID;
	if (Players.find(playerID) == Players.end()){
		logger().error("Could not find player" + playerID);
		return;
	}
	packet.spriteID = stringToCRC(Players[playerID]->name);
	playerContainer::iterator iter;
	for (iter = Players.begin(); iter != Players.end(); ++iter){
		
		socket.sendTo((const void *)&packet, sizeof(spriteDeletionPacket), iter->second->address);
	}
	logger().information("Player " + Players[playerID]->playerSprite->name + " has disconnected");
	sprite.removeSprite(packet.spriteID);
	Players.erase(playerID);
	
}
