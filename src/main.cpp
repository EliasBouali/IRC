#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <iostream>
#include <signal.h> 

int main()
{
    Server srv(6667, "password123");

    // Enregistrer le signal handler
    signal(SIGINT, Server::signalHandler);  // ← ajoute ça

    std::cout << "Initializing server on port 6667..." << std::endl;
    srv.init();
    std::cout << "Server is running. Press Ctrl+C to stop." << std::endl;

    srv.run();

    std::cout << "Server stopped." << std::endl;
    return 0;
}
