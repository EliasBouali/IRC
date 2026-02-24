#ifndef SERVER_HPP
#define SERVER_HPP


#include <string>
#include <vector>
#include <map>

#include "Client.hpp"
#include "Channel.hpp"


class Server
{
  public:
    Server(int port, const std::string &password);
    ~Server();

    void init();
    void acceptClient();
    void run();
    void handleClientData(int client_fd);
    void disconnectClient(int client_fd);
    static void signalHandler(int signal);

  private:
    Server(const Server &src);
    Server &operator=(const Server &src);

    static bool _running;
    Client* findClientByFd(int fd);
    void processMessage(const std::string &raw_message);

    int _serverFd;
    int _port;
    std::string _password;
    std::vector<Client*> _clients;
    std::map<std::string, Channel> _channels;
    std::vector<struct pollfd> _pollfds;

};

#endif
