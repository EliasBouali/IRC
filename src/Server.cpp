#include "Server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cerrno>

Server::Server(int port, const std::string &password)
: _serverFd(-1), _port(port), _password(password)
{
}

Server::~Server(){}

void Server::init()
{
  _serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (_serverFd == -1)
  {
    std::cerr << "Error: socket() failed" << std::endl;
    return ;
  }

  int value_option = 1;
  if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &value_option, sizeof(value_option)) < 0)
  {
    std::cerr << "Error setsockopt() failed" << std::endl;
    close(_serverFd);
    return ;
  }

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(_port);

  if (bind(_serverFd,(struct sockaddr*)&address,sizeof(address)) < 0)
  {
    std::cerr << "Error bind() failed" << std::endl;
    close(_serverFd);
    return ;
  }

  if (listen(_serverFd, 10) < 0)
  {
    std::cerr << "Error listen() failed" << std::endl;
    close(_serverFd);
    return ;
  }
}
