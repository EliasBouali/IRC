#include "Client.hpp"

Client::Client(int fd)
:_fd(fd), _nickname(""), _username(""), _authenticated(false)
{
}

Client::~Client(){}

int Client::getFd() const
{
  return _fd;
}

std::string& Client::getBuffer()
{
  return _buffer;
}
