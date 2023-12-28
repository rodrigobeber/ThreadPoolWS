#include <sys/socket.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <optional>
#include "network/SocketNetworkService.h"

SocketNetworkService::SocketNetworkService(size_t port, size_t maxQueuedConnections, IConcurrencyModel* concurrencyModel, IHttpHandler* httpHandler) :
        port(port), maxQueuedConnections(maxQueuedConnections), isRunning(false), concurrencyModel(concurrencyModel), httpHandler(httpHandler) {
    setupSocket();
}

SocketNetworkService::~SocketNetworkService() {
    stop();
}

void SocketNetworkService::start() {

    if (isRunning) {
        std::cerr << "Server is already running!" << std::endl;
        return;
    }

    bindSocket();
    startListening();

    isRunning = true;
    std::cout << "Server started on port " << port << std::endl;

    acceptConnections();
}

void SocketNetworkService::stop() {
    if (isRunning) {
        close(server_fd);
        isRunning = false;
        std::cout << "Server stopped." << std::endl;
    }
}

void SocketNetworkService::setupSocket() {
    // Create an endpoint comunication for IPv4 / TCP
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        throw std::runtime_error("Socket creation failed");
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        throw std::runtime_error("setsockopt failed");
    }

    address.sin_family = AF_INET; // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Bind to all available interfaces
    address.sin_port = htons(port); // Port to listen on
}

void SocketNetworkService::acceptConnections() {

    while (isRunning) {
        socklen_t addrlen = sizeof(address);
        int client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        // handle the connection
        concurrencyModel->execute([this, client_socket]() {
            this->handleConnection(client_socket);
        });
    }
}

std::optional<std::string> SocketNetworkService::readRequest(int client_socket) {
    const size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE] = {0};
    std::string request;

    ssize_t bytes_read;
    while (true) {
        bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);

        // Handle read errors or client disconnection
        if (bytes_read <= 0) {
            if (bytes_read < 0) {
                std::cerr << "Error reading from socket." << std::endl;
            } else {
                std::cerr << "Client closed the connection." << std::endl;
            }
            return std::nullopt;  // Return an empty optional to indicate the failure
        }

        request.append(buffer, bytes_read);

        // Check if the end of the request has been reached.
        if (request.find("\r\n\r\n") != std::string::npos) {
            break;
        }
    }

    return request;
}

void SocketNetworkService::handleConnection(int client_socket) {

    std::optional<std::string> request = readRequest(client_socket);
    if (!request) {
        close(client_socket);
        return;
    }

    std::string response = httpHandler->handleRequest(request.value());

    // Send the response
    send(client_socket, response.c_str(), response.size(), 0);

    // Close the connection
    close(client_socket);
}

void SocketNetworkService::bindSocket() {
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        throw std::runtime_error("Bind failed");
    }
}

void SocketNetworkService::startListening() {
    if (listen(server_fd, MAX_QUEUED_CONN) < 0) {
        throw std::runtime_error("Listen failed");
    }
}