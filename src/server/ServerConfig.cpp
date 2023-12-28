#include <iostream>
#include <cstdlib>
#include "server/ServerConfig.h"

void ServerConfig::parseArguments(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if ((arg == "-p" || arg == "--port") && i + 1 < argc) {
            port = static_cast<size_t>(std::atoi(argv[++i]));
        } else if ((arg == "-t" || arg == "--threads") && i + 1 < argc) {
            poolSize = static_cast<size_t>(std::atoi(argv[++i]));
        } else if ((arg == "--max-connections") && i + 1 < argc) {
            maxQueuedConnections = static_cast<size_t>(std::atoi(argv[++i]));
        } else {
            std::cerr << "Invalid or incomplete argument: " << arg << std::endl;
            exit(1);
        }
    }
}