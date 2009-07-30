#include <Poco/Util/PropertyFileConfiguration.h>
#include <fstream>
#include <string>
#include <vector>
#include "ProfileManager.hpp"
#include "menu/menuManager.hpp"
#include "helpers.hpp"

ProfileManager::ProfileManager()
{
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
		loadProfile(profiles[i]);
		menu->addProfile(profileList[i]);
	}
}

void ProfileManager::loadProfile(std::string name)
{
	Profile newProfile;
	newProfile.name = name;
	profileList.push_back(newProfile);
}