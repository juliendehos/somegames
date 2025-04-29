#pragma once

#include "../Game/Game.hpp"

#include <vector>

template<typename T>
std::vector<T> setToVector(const std::set<T> & s) {
  return std::vector<T>(s.begin(), s.end());
}

class Bot {
  private:
    std::string _name;

  public:
    Bot(const std::string & name);

    virtual ~Bot() = default;

    virtual Position genMove(const Game & g) = 0;

    virtual bool isHuman() const;

    const std::string & getName() const;
};

