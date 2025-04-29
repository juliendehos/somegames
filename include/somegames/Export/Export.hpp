#pragma once

#include "../Game/Game.hpp"

struct GameData {

  std::string name;
  Status status;
  std::set<Position> red_positions;
  std::set<Position> blue_positions;
  std::vector<Position> history;

};

GameData mkGameData(const Game & g);

