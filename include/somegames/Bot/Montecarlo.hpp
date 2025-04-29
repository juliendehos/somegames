#pragma once

#include "Bot.hpp"

#include <random>

class Montecarlo : public Bot {
  private:
    std::default_random_engine _engine;
    int _totalSims;

  public:
    explicit Montecarlo(int totalSims);
    Position genMove(const Game & g) override;

  private:
    int evalMove(const Game & g, const Position & p, int nSims);
    Status randomPlayout(const Game & g);
    Position randomMove(const Game & g);
};


