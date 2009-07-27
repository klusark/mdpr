#include <Poco/Net/HTMLForm.h>
#include <Poco/Util/Application.h>
#include "networkMasterServer.hpp"
#include "RequestHandleFunctions.hpp"

handleMapContainer handleMap;

void FillMap()
{
	handleMap["/"] = (*Root);
	handleMap["/submit"] = (*Submit);
	handleMap["/servers"] = (*Servers);
}

void Root(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	std::ostream& ostr = response.send();
	int var = 5;
	ostr << 
		"<html>"
		"<head>"
		"<title>Testing</title>"
		"</head>"
		"<body>"
		"<form method='post' action='submit'>"
		"<input type='text' name='name' value='"
		<<var<<
		"'>"
		"<input type='submit' value='Submit'>"
		"</form>"
		"</body>"
		"</html>";
}

void Submit(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	//std::string test;
	Poco::Net::HTMLForm form(request, request.stream());
	
	std::ostream& ostr = response.send();
	ostr << 
		"<html>"
		"<head>"
		"<title>Submit</title>"
		"</head>"
		"<body>"
		<<form["name"]<<
		"</body>"
		"</html>";
}

void Servers(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	std::ostream& ostr = response.send();
	ostr << 
		"<html>"
		"<head>"
		"<title>Servers</title>"
		"</head>"
		"<body>"
		"<table border='1'>";
	Poco::Util::Application* app = &Poco::Util::Application::instance();
	NetworkMasterServer* server = dynamic_cast<NetworkMasterServer*>(app);
	NetworkMasterServer::serverListContainer::iterator it;
	for (it = server->serverList.begin(); it != server->serverList.end(); ++it){
		ostr << "<tr><td></td></tr>";
	}
	ostr <<
		"</table>"
		"</body>"
		"</html>";
}
