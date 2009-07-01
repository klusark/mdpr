#include <iostream>
#include <exception>
#include <SFML/System/Sleep.hpp>

#include "enumerations.hpp"
#include "MDPRGame.hpp"

#include "sprite/clientSpriteManager.hpp"
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

		
	for (short i = 0; i < numServerUpdateThreads; ++i){
		serverListUpdateThreads.create_thread(boost::bind(&networkClient::serverListUpdateThread, this, i));
	}
}

networkClient::~networkClient()
{
	ioService.stop();
	ioServiceThreadPool.join_all();
	//delete ioThread;

}

void networkClient::connectToServer(std::string ip, std::string port)
{
	connectPacket packet;
	packet.packetID = connectPacketID;
	packet.nameLength = MDPR->playerName.length();
	strcpy(packet.name, MDPR->playerName.c_str());

	udp::resolver resolver(ioService);
	udp::resolver::query query(udp::v4(), ip, port);
	receiverEndpoint = *resolver.resolve(query);
	
	socket.send_to(boost::asio::buffer((const void *)&packet, 6 + packet.nameLength), receiverEndpoint);
	currentState = connectingState;
	connected = true;
}

void networkClient::connectToServer(serverEntry entry)
{
	std::string ip = "";
	char segment[4];
	for (int x = 0; x < 4; ++x){
		
		sprintf(segment, "%d", entry.ip[x]);
		ip += segment;
		if (x != 3){
			ip += ".";
		}
	}
	char portChar[6];
	std::string port;
	sprintf(portChar, "%d", entry.port);
	port = portChar;
	connectToServer(ip, port);
}

void networkClient::connectToMaster()
{
	getServersPacket packet;
	packet.packetID = getServersPacketID;

	udp::resolver resolver(ioService);
	udp::resolver::query query(udp::v4(), MDPR->serverIP, "9937");
	masterServerEndpoint = *resolver.resolve(query);
	
	socket.send_to(boost::asio::buffer((const void *)&packet, 4), masterServerEndpoint);
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
				boost::shared_ptr<ClientSprite> newSprite(new ClientSprite(packet->name));
				newSprite->SetImage(*sprite.Images[packet->spriteType].get());
				sprite.registerSprite(newSprite);
				
			}
			break;
		case spriteTypeCreationPacketID:
			{
				spriteTypeCreationPacket *packet = (spriteTypeCreationPacket *)buffer;
				boost::shared_ptr<sf::Image> Image(new sf::Image);
				std::string fileName;
				fileName += "data/";
				fileName += packet->fileName;
				if (!Image->LoadFromFile(fileName)){
					std::exception exception;
					//exception.
					throw exception;
				}
				

				Image->SetSmooth(false);
				sprite.Images[packet->spriteTypeID] = Image;
			}
			break;
		case animationCreationPacketID:
			{
				animationCreationPacket *packet = (animationCreationPacket *)buffer;
				sprite.Animations[packet->animationID] = *packet;
			}
			break;
		case spritePosPacketID:
			{
				spritePosPacket *packet = (spritePosPacket *)buffer;
				boost::mutex::scoped_lock lock(sprite.spriteMutex);
				if (sprite.Sprites.find(packet->spriteID) == sprite.Sprites.end()){
					cannotFindSpritePacket newPacket;
					newPacket.packetID = cannotFindSpritePacketID;
					newPacket.spriteID = packet->spriteID;
					socket.send_to(boost::asio::buffer((const void *)&newPacket, sizeof(cannotFindSpritePacket)), receiverEndpoint);
					//std::cout << "Could not find sprite" << std::endl;
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
				sprite.Sprites[packet->spriteID]->currentAnimationID = packet->animationID;
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
				sprite.Sprites[packet->spriteID]->currentFrame = packet->currentFrame;
			}
			break;
		case serversListPacketID:
			{
				serversListPacket *packet = (serversListPacket *)buffer;
				for (unsigned short i = 0; i < packet->numServers; ++i){
					fullServerEntry newEntry;
					memcpy((void *)&newEntry.entry, (void *)&packet->serverList[i], sizeof(serverEntry));
					//serverList.push_back(newEntry);
					serversToUpdate[0].push_back(&newEntry);
				}
			}
			break;
		case fullServerInfoPacketID:
			{
				fullServerInfoPacket *packet = (fullServerInfoPacket *)buffer;
				fullServerEntry newEntry;

				memcpy(newEntry.entry.ip, receiverEndpoint.address().to_v4().to_bytes().elems, 4);
				newEntry.entry.port = packet->port;
				newEntry.maxPlayers = packet->maxPlayers;
				newEntry.numPlayers = packet->numPlayers;
				newEntry.serverName = packet->serverName;
				serverList.push_back(newEntry);

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
			sf::Sleep(0.002f);
		}else{
			//boost::asio::io_service ioService;
			udp::resolver resolver(ioService);
			std::string test;
			//char *buffers;
			//buffers = new char[6];
			for (int x = 0; x < 4; ++x){
				char temp[3];
				sprintf(temp, "%d", serversToUpdate[i][0]->entry.ip[x]);
				test += temp;
				if (x != 3){
					test += ".";
				}
			}
			char buffer[6];
			//buffer = new char[6];
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
	MDPRGame::quitGame();
}
