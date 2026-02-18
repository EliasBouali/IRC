#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>

#include "Client.hpp"

class Channel
{
  public:
    Channel(const std::string &name);
    ~Channel();

  private:
    Channel(const Channel &other);
    Channel &operator=(const Channel &other);

    std::string _name;
    std::string _subject;
    std::vector<Client*> _members;
    std::vector<Client*> _operators;

    bool _inviteOnly;
    bool _topicRestricted;
    std::string _key;
    int _userLimit;

};

#endif
