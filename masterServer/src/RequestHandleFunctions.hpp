#ifndef RquestHandleFunctions_hpp
#define RquestHandleFunctions_hpp

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <map>

typedef std::map<std::string, void (*)(Poco::Net::HTTPServerRequest&, Poco::Net::HTTPServerResponse&)> handleMapContainer;
extern handleMapContainer handleMap;

void FillMap();

void Root(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
void Submit(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
void Servers(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

#endif // #ifndef RquestHandleFunctions_hpp
