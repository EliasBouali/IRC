#include "Client.hpp"

Client::Client(int fd)
:_fd(fd), _nickname(""), _username(""), _authenticated(false)
{
  (void)fd;
}

Client::~Client(){}

int Client::getFd() const
{
  return _fd;
}
