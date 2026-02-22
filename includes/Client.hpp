#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
  public:
    Client(int fd);
    ~Client();

    int getFd() const;

  private:
    Client(const Client &name);
    Client &operator=(const Client &other);

    int _fd;
    std::string _nickname;
    std::string _username;
    bool _authenticated;

};
#endif
