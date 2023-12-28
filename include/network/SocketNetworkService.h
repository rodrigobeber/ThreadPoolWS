#pragma once

#include <netinet/in.h>
#include <string>
#include <optional>
#include "network/INetworkService.h"
#include "network/IHttpHandler.h"
#include "concurrency/ThreadPoolConcurrency.h"

class SocketNetworkService : public INetworkService {
private:
    int server_fd;
    struct sockaddr_in address;
    const int MAX_QUEUED_CONN {100};
    size_t port;
    size_t maxQueuedConnections;
    bool isRunning;
    IConcurrencyModel* concurrencyModel;
    IHttpHandler* httpHandler;

    void setupSocket();
    void bindSocket();
    void startListening();
    void acceptConnections();
    void handleConnection(int client_socket);
    std::optional<std::string> readRequest(int client_socket);

public:
    explicit SocketNetworkService(size_t port, size_t maxQueuedConnections, IConcurrencyModel* concurrencyModel, IHttpHandler* handler);
    ~SocketNetworkService();

    void start() override;
    void stop() override;
};
