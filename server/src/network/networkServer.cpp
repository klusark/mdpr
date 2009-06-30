//#include <boost/asio.hpp>
//#include <boost/bind.hpp>
#include "helpers.hpp"
//#include <boost/date_time/posix_time/posix_time.hpp>
#include <Poco/SharedPtr.h>
#include <Poco/NObserver.h>
#include <Poco/Thread.h>
//#include <boost/thread.hpp>

//#include <iostream>
#include <map>
#include <vector>

#include "networkServer.hpp"
#include "network/packets.hpp"
#include "sprite/spriteManager.hpp"
#include "sprite/genericSprite.hpp"
#include "sprite/player.hpp"
#include "sprite/platform.hpp"
#include "sprite/bubble.hpp"

POCO_SERVER_MAIN(NetworkServer)

//using boost::asio::ip::udp;

Poco::SharedPtr<NetworkServer> server;

NetworkServer::NetworkServer() 
	:	buffer(new char[BUFFER_SIZE]),
		spriteUpdateTimer(250, 5)
		
//	:	serverSocket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 9935)),
//		spriteUpdateTimer(ioService, boost::posix_time::seconds(2)),
//		masterServerUpdateTimer(ioService, boost::posix_time::seconds(1)),
//		removeIdlePlayersTimer(ioService, boost::posix_time::seconds(10))
{
	posUpdate = 0;

	//serverSocket.async_receive_from(boost::asio::buffer(buffer), endpoint, boost::bind(&NetworkServer::onReceivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

/*	udp::resolver resolver(ioService);
	udp::resolver::query query(udp::v4(), "5.95.76.52", "9937");
	masterServerEndpoint = *resolver.resolve(query);

	spriteUpdateTimer.async_wait(boost::bind(&NetworkServer::onSpriteUpdate, this, boost::asio::placeholders::error));
	masterServerUpdateTimer.async_wait(boost::bind(&NetworkServer::updateMasterServer, this, boost::asio::placeholders::error));
	removeIdlePlayersTimer.async_wait(boost::bind(&NetworkServer::removeIdlePlayers, this, boost::asio::placeholders::error));

	for (short i = 0; i < numIOServiceThreads; ++i){
		ioThreads.create_thread(boost::bind(&NetworkServer::ioServiceThread, this));
	}
*/
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

	socketAddress = Poco::Net::SocketAddress("0.0.0.0", config().getInt("Server.port"));
	// set-up a server socke
	socket.bind(socketAddress, true);
	// set-up a SocketReactor...
	Poco::Net::SocketReactor reactor;
	reactor.addEventHandler(socket, Poco::NObserver<NetworkServer, Poco::Net::ReadableNotification>(*this, &NetworkServer::onReceivePacket));
	// run the reactor in its own thread so that we can wait for
	// a termination request
	
	//spriteUpdateTimer = Poco::AutoPtr<Poco::Util::TimerTaskAdapter<NetworkServer> >(new Poco::Util::TimerTaskAdapter<NetworkServer>(*this, &NetworkServer::onSpriteUpdate));
	//taskManager.
	spriteUpdateTimer.start(Poco::TimerCallback<NetworkServer>(*this, &NetworkServer::onSpriteUpdate));

	Poco::Thread thread;
	thread.start(reactor);
	if (config().getBool("Server.Master.updateToMaster", false)){
		unsigned short masterServerPort = (unsigned short)config().getInt("Server.Master.port", 9937);
		std::string masterServerIP = config().getString("Server.Master.ip");
		if (masterServerIP.length() != 0){
			masterServerAddress = Poco::Net::SocketAddress(masterServerIP, masterServerPort);
			socket.sendTo((const void *)&packetServerInfo, sizeof(serverInfoPacket), masterServerAddress);
		}
	}
	// wait for CTRL-C or kill
	waitForTerminationRequest();
	// Stop the SocketReactor
	reactor.stop();
	thread.join();

	return Application::EXIT_OK;
}

void NetworkServer::onReceivePacket(const Poco::AutoPtr<Poco::Net::ReadableNotification>& pNf)
{
	socket.receiveFrom(buffer, BUFFER_SIZE, socketAddress);
	/*//if (error){
		//std::cout << "onReceivePacket: " << error.message() << std::endl;

		if (!(Players.find(endpoint.port()) == Players.end())){

			disconnect(endpoint.port());

		}
	//}else{*/
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

			std::string name = packet->name;//, packet->nameLength);

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
			player->name = packet->name;

			Poco::SharedPtr<genericSprite> newPlayer(new Player(packet->name));
			
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
					socket.sendTo((const void *)&packet, sizeof(spriteCreationPacket) + packet.nameLength - 255, player->address);
					
				}
			}

			{
				//Sends the current animation and position of all the sprites to the new player
				spriteManager::spriteContainer::iterator iter;
				for(iter = sprite.Sprites.begin(); iter != sprite.Sprites.end(); ++iter){
					if(iter->second->nonNetworked){
						continue;
					}
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
}

/*void NetworkServer::handleSendTo(const boost::system::error_code& error, size_t bytes_sent)
{
	if (error){
		std::cout << "handleSendTo: " <<  error.message() << std::endl;
		return;
	}
}*/

/*void NetworkServer::removeIdlePlayers(const boost::system::error_code& error)
{
	//boost::mutex::scoped_lock lock(PlayerMutex);
	for (NetworkServer::playerContainer::iterator it = Players.begin(); it != Players.end(); ++it){
		if (!it->second->stillAlive){
			//disconnect(it->first);
			break;
		}else{
			it->second->stillAlive = false;
		}
	}
	removeIdlePlayersTimer.expires_from_now(boost::posix_time::seconds(10));
	removeIdlePlayersTimer.async_wait(boost::bind(&NetworkServer::removeIdlePlayers, this, boost::asio::placeholders::error));
}

*/
void NetworkServer::onSpriteUpdate(Poco::Timer& timer)
{
	/*if (error){
		std::cout << "onSpriteUpdate: " << error.message() << std::endl;
		return;
	}*/
	boost::mutex::scoped_lock lock(sprite.spriteMutex);
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
				//serverSocket.async_send_to(boost::asio::buffer((const void *)&animationPacket, sizeof(animationPacket)), iter->second->endpoint, boost::bind(&NetworkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
			}
			socket.sendTo((const void *)&packet, sizeof(positionAndFrameUpdatePacket), iter->second->address);
			//serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, sizeof(packet)), iter->second->endpoint, boost::bind(&NetworkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
	}
	//spriteUpdateTimer.expires_from_now(boost::posix_time::milliseconds(5));
	//spriteUpdateTimer.async_wait(boost::bind(&NetworkServer::onSpriteUpdate, this, boost::asio::placeholders::error));

}
/*
void NetworkServer::updateMasterServer(const boost::system::error_code& error)
{
	if (error){
		std::cout << "updateMasterServer: " << error.message() << std::endl;
		return;
	}

	serverSocket.send_to(boost::asio::buffer((const void *)&packetServerInfo, 6), masterServerEndpoint);

	masterServerUpdateTimer.expires_from_now(boost::posix_time::seconds(15));
	masterServerUpdateTimer.async_wait(boost::bind(&NetworkServer::updateMasterServer, this, boost::asio::placeholders::error));
}

void NetworkServer::disconnect(unsigned short playerID)
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
		serverSocket.async_send_to(boost::asio::buffer((const void *)&packet, sizeof(packet)), iter->second->endpoint, boost::bind(&NetworkServer::handleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
	std::cout << "Player " << Players[playerID]->playerSprite->name << " has disconnected." << std::endl;
	//Players[playerID]->timer.cancel();
	sprite.removeSprite(packet.spriteID);
	Players.erase(playerID);
	
}

void NetworkServer::playerInfo::disconnect(const boost::system::error_code& error)
{
	if (error){
		std::cout << "disconnect: " << error.message() << std::endl;
		return;
	}
	server->disconnect(endpoint.port());
}

void NetworkServer::ioServiceThread()
{
	try{
		ioService.run();
	}catch (std::exception& e){
		std::cout << "Exception: " << e.what() << std::endl;
	}catch(...){
		std::cout << "Unknown Exception caught" << std::endl; 
	}
	std::cout << "ioServiceThread: Huge error. FIX ME!!!" << std::endl;
}
*/