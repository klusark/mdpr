#ifndef ProfileManager_hpp
#define ProfileManager_hpp

#include <vector>
#include "network/packets.hpp"
#include "Profile.hpp"

//!Manages all the user profiles
/*!
Includes doing:
Updating stats from the master
Creating new profiles
Saving profiles
*/
class ProfileManager
{
public:

	//!Constructor
	ProfileManager();

	//!Deconstructor
	~ProfileManager();

	//!Loads all of the profiles
	void loadProfiles();

	//!Connects the selected profiles to a server
	void connectToServer(serverEntry entry);

	void sendKeyPress(sf::Key::Code key, bool down);

	bool isConnected() const {return connected;};

	//!Loads a profile
	/*!
	@param name the name of the profile to load
	*/
	void ProfileManager::loadProfile(std::string name, Poco::Util::PropertyFileConfiguration& propertyFile);

	//!The type for the profileList
	typedef std::vector<Poco::SharedPtr<Profile>> profileListType;

	//!the list of profiles
	profileListType profileList;

	typedef std::vector<Profile*> profileListPtrType;

	//!the list of selected profiles
	profileListPtrType selectedProfileList;

private:
	bool connected;

};

#endif // #ifndef ProfileManager_hpp