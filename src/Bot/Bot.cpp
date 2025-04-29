
#include <somegames/Bot/Bot.hpp>

Bot::Bot(const std::string & name) : _name(name) {}

bool Bot::isHuman() const {
  return false;
}

const std::string & Bot::getName() const {
  return _name;
}

