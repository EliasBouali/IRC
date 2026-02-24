#include "Server.hpp"
#include <iostream>
#include <signal.h>
#include <cstdlib>

int main(int argc, char **argv)
{
    int port = 6667;
    std::string password = "password123";

    if (argc == 3)
    {
        port = atoi(argv[1]);
        password = argv[2];

        if (port <= 0 || port > 65535)
        {
            std::cerr << "Error: Invalid port (1-65535)" << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << "[DEV MODE] Using default: port=" << port
                  << " password=" << password << std::endl;
        std::cout << "[DEV MODE] Usage: " << argv[0]
                  << " <port> <password> for production mode" << std::endl;
        std::cout << std::endl;
    }

    Server srv(port, password);
    signal(SIGINT, Server::signalHandler);

    std::cout << "Initializing server on port " << port << "..." << std::endl;
    srv.init();
    std::cout << "Server is running. Press Ctrl+C to stop." << std::endl;

    srv.run();

    std::cout << "Server stopped." << std::endl;
    return 0;
}
