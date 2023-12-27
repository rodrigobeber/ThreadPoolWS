#pragma once

#include <string>

class IHttpHandler {
public:
    virtual std::string handleRequest(const std::string& request) = 0;
    virtual ~IHttpHandler() {}
};
