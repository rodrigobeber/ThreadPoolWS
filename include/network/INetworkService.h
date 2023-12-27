#pragma once

class INetworkService {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~INetworkService() = default;
};
