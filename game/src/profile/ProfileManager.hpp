#ifndef ProfileManager_hpp
#define ProfileManager_hpp

#include <vector>
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

	//!Loads a profile
	/*!
	@param name the name of the profile to load
	*/
	void ProfileManager::loadProfile(std::string name);

	//!The type for the profileList
	typedef std::vector<Profile> profileListType;

	//!the list of profiles
	profileListType profileList;

};

#endif // #ifndef ProfileManager_hpp