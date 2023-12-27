#include "server/Server.h"

Server::Server(INetworkService* networkService) : networkService(networkService) {}

void Server::run() {
    networkService->start();
}

Server::~Server() {
    networkService->stop();
}
