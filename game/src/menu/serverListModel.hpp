#ifndef serverListModel_hpp
#define serverListModel_hpp

#include <guichan/listmodel.hpp>
#include <vector>

class ServerListModel : public gcn::ListModel
{
public:
	ServerListModel();
	~ServerListModel();
	int getNumberOfElements();
	std::string getElementAt(int i);
private:
	//std::vector<std::string> list;
};

#endif // #ifndef serverListModel_hpp