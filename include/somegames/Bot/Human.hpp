#pragma once

#include "Bot.hpp"

class Human : public Bot {
  public:
    Human();
    Position genMove(const Game & g) override;
    bool isHuman() const override;
};



