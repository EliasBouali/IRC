#include "Server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <arpa/inet.h>
#include <poll.h>

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


void Server::acceptClient()
{
  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);

  int client_fd = accept(_serverFd, (struct sockaddr*)&client_addr, &client_len);

  if (client_fd < 0)
  {
    std::cerr << "Error: accept() failed" << std::endl;
    return;
  }

  std::cout << "New connection from "
          << inet_ntoa(client_addr.sin_addr)
          << ":" << ntohs(client_addr.sin_port)
          << std::endl;

  Client* newClient = new Client(client_fd);
  _clients.push_back(newClient);

  struct pollfd client_pfd;
  client_pfd.fd = client_fd;
  client_pfd.events = POLLIN;
  client_pfd.revents = 0;
  _pollfds.push_back(client_pfd);

  std::cout << "Client added. Total clients: " << _clients.size() << std::endl;

}


void Server::handleClientData(int client_fd)
{
  char buffer[1024];
  int bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

  if (bytes_read <= 0)
  {
    std::cout << "Client " << client_fd << " disconnected" << std::endl;
    disconnectClient(client_fd);
  }
  else
  {
    buffer[bytes_read] = '\0';
    std::cout << "Client " << client_fd << " sent: " << buffer;
  }
}

void Server::run()
{
  struct pollfd server_pfd;
  server_pfd.fd = _serverFd;
  server_pfd.events = POLLIN;
  server_pfd.revents = 0;
  _pollfds.push_back(server_pfd);

  while (true)
  {
    int poll_count = poll(&_pollfds[0], _pollfds.size(), -1);
    if (poll_count < 0)
    {
      std::cerr << "Error: poll() failed" << std::endl;
      break;
    }

    for (size_t i = 0; i < _pollfds.size(); i++)
    {
      if (_pollfds[i].revents & POLLIN)
      {
        if (_pollfds[i].fd == _serverFd)
          acceptClient();
        else
          handleClientData(_pollfds[i].fd);
      }
    }
  }
}

void Server::disconnectClient(int client_fd)
{
  for (size_t i = 0; i < _pollfds.size(); i++)
  {
    if (_pollfds[i].fd == client_fd)
    {
      _pollfds.erase(_pollfds.begin() + i);
      break;
    }
  }

  for (size_t i = 0; i < _clients.size(); i++)
  {
    if (_clients[i]->getFd() == client_fd)
    {
      delete _clients[i];
      _clients.erase(_clients.begin() + i);
      break;
    }
  }
  close(client_fd);
}
