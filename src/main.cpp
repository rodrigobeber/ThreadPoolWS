#include "server/Server.h"
#include "concurrency/ThreadPoolConcurrency.h"
#include "network/SocketNetworkService.h"
#include "network/BasicHttpHandler.h"

int main() {
    int port = 8080;
    int poolSize = 4;

    // setup network service
    BasicHttpHandler httpHandler;
    ThreadPoolConcurrency concurrencyModel(poolSize);
    SocketNetworkService networkService(port, &concurrencyModel, &httpHandler);

    // server
    Server server(&networkService);
    server.run();

    return 0;
}