#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <iostream>

int main()
{
    Server srv(6667, "password123");

    std::cout << "Initializing server on port 6667..." << std::endl;
    srv.init();
    std::cout << "Server is running. Press Ctrl+C to stop." << std::endl;

    srv.run();  // ← boucle infinie avec poll()

    return 0;
}
