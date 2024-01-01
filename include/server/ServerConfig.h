#pragma once

#include <cstddef>

struct ServerConfig {
    size_t port = 8080;
    size_t poolSize = std::thread::hardware_concurrency();
    size_t maxQueuedConnections = 100;
    void parseArguments(int argc, char* argv[]);
};