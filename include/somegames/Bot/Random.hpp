#pragma once

#include "Bot.hpp"

#include <random>

class Random : public Bot {
  private:
    std::default_random_engine _engine;

  public:
    Random();
    Position genMove(const Game & g) override;
};


