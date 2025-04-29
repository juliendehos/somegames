
#include <somegames/Export/Export.hpp>

GameData mkGameData(const Game & g) {
  return {
    g.getName(),
    g.getStatus(),
    g.getRedPositions(),
    g.getBluePositions(),
    g.getHistory()
  };
}

