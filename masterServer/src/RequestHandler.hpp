#ifndef RquestHandler_hpp
#define RquestHandler_hpp

#include <Poco/Net/HTTPRequestHandler.h>

class RequestHandler : public Poco::Net::HTTPRequestHandler
	/// Return a HTML document with the current date and time.
{
public:
	RequestHandler();

	
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

};

#endif // #ifndef RquestHandler_hpp
