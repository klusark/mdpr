#ifndef Profile_hpp
#define Profile_hpp

#include <string>
#include <Poco/SharedPtr.h>

#include "network/networkClient.hpp"

//!A profile to be managed by ProfileManager
/*!

*/
class Profile
{
public:
	//!constructor
	Profile();
	//!deconstructor
	~Profile();
	//!the name of the profile
	std::string name;

	Poco::SharedPtr<NetworkClient> networkClient;

	struct
	{
		char up, down, left, right, use;
	}controls;
};


#endif // #ifndef Profile_hpp
