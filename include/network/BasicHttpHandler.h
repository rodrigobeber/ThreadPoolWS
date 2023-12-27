#pragma once

#include "IHttpHandler.h"

class BasicHttpHandler : public IHttpHandler {
public:
    std::string handleRequest(const std::string& request) override;
};
