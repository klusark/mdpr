#include <Poco/Util/Application.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include "RequestHandler.hpp"
#include "RequestHandleFunctions.hpp"

RequestHandler::RequestHandler() 
{
}
	
void RequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	Poco::Util::Application& app = Poco::Util::Application::instance();
	app.logger().information("Request from " + request.clientAddress().toString());

	response.setChunkedTransferEncoding(true);
	response.setContentType("text/html");
	handleMapContainer::iterator it;
	if ((it = handleMap.find(request.getURI())) != handleMap.end()){
		it->second(request, response);
	}else{
		std::ostream& ostr = response.send();
		ostr << "404";
		response.setReason("404");
	}

}
