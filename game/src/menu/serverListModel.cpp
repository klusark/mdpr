#include "serverListModel.hpp"
#include "MDPRGame.hpp"

ServerListModel::ServerListModel()
{
}

ServerListModel::~ServerListModel()
{
}


int ServerListModel::getNumberOfElements()
{
	return MDPR->myNetworkClient->serverList.size();
}

std::string ServerListModel::getElementAt(int i)
{
	return MDPR->myNetworkClient->serverList[i].serverName;
}