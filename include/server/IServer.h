#pragma once

class IServer {
public:
    virtual void run() = 0;
    virtual ~IServer() {}
};
