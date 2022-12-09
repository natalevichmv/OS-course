#include <string>
#include <iostream>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <Poco/StreamCopier.h>

int main() {
    Poco::URI uri("http://jsonplaceholder.typicode.com/todos/1");
    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());

    std::string path(uri.getPathAndQuery());
    if (path.empty()) {
        path = "/";
    }
    Poco::Net::HTTPRequest request(
        Poco::Net::HTTPRequest::HTTP_GET,
        path,
        Poco::Net::HTTPMessage::HTTP_1_1);
    session.sendRequest(request);

    Poco::Net::HTTPResponse response;
    std::istream& in = session.receiveResponse(response);
    Poco::StreamCopier::copyStream(in, std::cout);

    std::cout << std::endl;
    std::cout << "Response code: " << response.getStatus() 
              << " " << response.getReason() << std::endl;
    return 0;
}