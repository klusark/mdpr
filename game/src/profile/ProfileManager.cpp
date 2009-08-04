#include <Poco/Util/PropertyFileConfiguration.h>
#include <fstream>
#include <string>
#include <vector>
#include "ProfileManager.hpp"
#include "menu/menuManager.hpp"
#include "helpers.hpp"

ProfileManager::ProfileManager()
{
	connected = false;
	loadProfiles();
}

ProfileManager::~ProfileManager()
{
}

void ProfileManager::loadProfiles()
{
	//Clear the list so we can fill it with the latest profiles
	profileList.clear();

	std::string file = "data/profiles/profiles.properties";
	std::ifstream spriteFileStream(file.c_str());
	if (!spriteFileStream.is_open()){
		//If the file was not found throw
		throw;
	}

	Poco::Util::PropertyFileConfiguration *propertyFile = new Poco::Util::PropertyFileConfiguration(spriteFileStream);

	std::string str = propertyFile->getString("profiles");
	std::vector<std::string> profiles =  splitString(str, ",");

	for (unsigned int i = 0; i < profiles.size(); ++i){
		loadProfile(profiles[i], *propertyFile);
		menu->addProfile(*profileList[i].get());
	}
}

void ProfileManager::loadProfile(std::string name, Poco::Util::PropertyFileConfiguration& propertyFile)
{
	
	Poco::SharedPtr<Profile> newProfile;
	newProfile.assign(new Profile);
	newProfile->name = name;
	newProfile->controls.up =		propertyFile.getString("profile." + name + ".controls.up").c_str()[0];
	newProfile->controls.down =		propertyFile.getString("profile." + name + ".controls.down").c_str()[0];
	newProfile->controls.left =		propertyFile.getString("profile." + name + ".controls.left").c_str()[0];
	newProfile->controls.right =	propertyFile.getString("profile." + name + ".controls.right").c_str()[0];
	newProfile->controls.use =		propertyFile.getString("profile." + name + ".controls.use").c_str()[0];
	profileList.push_back(newProfile);
}

void ProfileManager::connectToServer(serverEntry entry)
{
	connected = true;
	for (unsigned int i = 0; i < selectedProfileList.size(); ++i){
		bool noSpriteUpdate = true;
		if (i == 0){
			noSpriteUpdate = false;
		}
		selectedProfileList[i]->networkClient.assign(new NetworkClient);
		selectedProfileList[i]->networkClient->connectToServer(entry, noSpriteUpdate, selectedProfileList[i]->name);
	}
}

void ProfileManager::sendKeyPress(sf::Key::Code key, bool down)
{
	for (unsigned int i = 0; i < selectedProfileList.size(); ++i){
		NetworkClient* networkClient = selectedProfileList[i]->networkClient.get();
		if (!networkClient->isInGame()){
			continue;
		}
		keyPacket packet;
		packet.packetID = keyPacketID;
		packet.down = down;
		if (key == selectedProfileList[i]->controls.right){
			packet.key = keyRight;
		}else if (key == selectedProfileList[i]->controls.left){
			packet.key = keyLeft;
		}else if (key == selectedProfileList[i]->controls.use){
			packet.key = keyAction;
		}else if (key == selectedProfileList[i]->controls.up){
			packet.key = keyUp;
		}else if (key == selectedProfileList[i]->controls.down){
			packet.key = keyDown;
		}else{
			continue;
		}

		networkClient->socket.sendTo((const void *)&packet, 9, networkClient->serverAddress);
	}
}
