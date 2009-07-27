#include "RequestHandler.hpp"
#include "RequestHandlerFactory.hpp"

RequestHandlerFactory::RequestHandlerFactory()
{
}

Poco::Net::HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new RequestHandler;
}
