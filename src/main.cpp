#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <iostream>

int main()
{
    Server srv(6667, "password123");

    std::cout << "Initializing server on port 6667..." << std::endl;
    srv.init();

    std::cout << "Server is listening. Press Ctrl+C to stop." << std::endl;

    // Boucle infinie pour garder le serveur actif
    while (true) {
        // Pour l'instant on fait rien, juste on reste actif
    }

    return 0;
}
