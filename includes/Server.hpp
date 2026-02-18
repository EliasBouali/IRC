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

  private:
    Server(const Server &src);
    Server &operator=(const Server &src);

    int _serverFd;
    int _port;
    std::string _password;
    std::vector<Client> _clients;
    std::map<std::string, Channel> _channels;

};

#endif
