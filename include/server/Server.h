#pragma once

#include "server/IServer.h"
#include "network/INetworkService.h"
#include "concurrency/IConcurrencyModel.h"

class Server : public IServer {
private:
    INetworkService* networkService;

public:
    Server(INetworkService* netService);
    void run() override;
    ~Server();
};