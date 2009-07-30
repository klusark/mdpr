#ifndef Profile_hpp
#define Profile_hpp

#include <string>

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
	struct
	{
		char up, down, left, right ,use;
	}controls;
};


#endif // #ifndef Profile_hpp
