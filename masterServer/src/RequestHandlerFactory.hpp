#ifndef RequestHandlerFactory_hpp
#define RequestHandlerFactory_hpp

#include <Poco/Net/HTTPRequestHandlerFactory.h>

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
	RequestHandlerFactory();

	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};

#endif // #ifndef RequestHandlerFactory_hpp
