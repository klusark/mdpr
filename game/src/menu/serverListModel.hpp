#ifndef serverListModel_hpp
#define serverListModel_hpp

#include <guichan/listmodel.hpp>

class ServerListModel : public gcn::ListModel
{
public:
	ServerListModel();
	~ServerListModel();
	int getNumberOfElements();
	std::string getElementAt(int i);
};

#endif // #ifndef serverListModel_hpp