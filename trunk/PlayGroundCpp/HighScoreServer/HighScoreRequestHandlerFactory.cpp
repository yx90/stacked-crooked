#include "HighScoreRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequestHandler.h"


namespace HighScoreServer
{

    Poco::Net::HTTPRequestHandler *
    HighScoreRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& inRequest)
    {
        if (inRequest.getURI() == "/")
        {
	        return new HighScoreRequestHandler;
        }
        return 0;
    }

} // namespace HighScoreServer
