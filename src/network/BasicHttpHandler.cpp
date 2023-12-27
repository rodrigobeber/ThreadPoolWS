#include "network/BasicHttpHandler.h"

std::string BasicHttpHandler::handleRequest(const std::string& request) {
    std::string responseBody = "This is a BasicHttpHandler";
    std::string response = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(responseBody.size()) + "\r\n\r\n" + responseBody;
    return response;
}