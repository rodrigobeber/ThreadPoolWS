#include "server/Server.h"
#include "server/ServerConfig.h"
#include "concurrency/ThreadPoolConcurrency.h"
#include "network/SocketNetworkService.h"
#include "network/BasicHttpHandler.h"

int main(int argc, char* argv[]) {
    ServerConfig config;
    config.parseArguments(argc, argv);

    // setup network service
    BasicHttpHandler httpHandler;
    ThreadPoolConcurrency concurrencyModel(config.poolSize);
    SocketNetworkService networkService(config.port, config.maxQueuedConnections, &concurrencyModel, &httpHandler);

    // server
    Server server(&networkService);
    server.run();

    return 0;
}