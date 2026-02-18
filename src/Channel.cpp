#include "Channel.hpp"

Channel::Channel(const std::string &name)
: _name(name), _subject(""), _members(), _operators(),
  _inviteOnly(false), _topicRestricted(false), _key(""), _userLimit(0)
{}

Channel::~Channel(){}
