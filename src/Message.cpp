#include "Message.hpp"
#include <sstream>


Message::Message(const std::string &raw)
{
  parse(raw);
}

Message::~Message() {}

std::string Message::getCommand() const
{
  return _command;
}

std::vector<std::string> Message::getParams() const
{
  return _params;
}

void Message::parse(const std::string &raw)
{
  size_t trailing_pos = raw.find(" :");

  std::string before_trailing;
  std::string trailing;

  if (trailing_pos != std::string::npos)
  {
    before_trailing = raw.substr(0, trailing_pos);
    trailing = raw.substr(trailing_pos + 2);
  }
  else
    before_trailing = raw;



  std::istringstream iss(before_trailing);
  std::string word;
  bool first = true;


  while (iss >> word)
  {
    if (first)
    {
      _command = word;
      first = false;
    }
    else
      _params.push_back(word);
  }
  if (!trailing.empty())
  {
    _params.push_back(trailing);
  }
}
