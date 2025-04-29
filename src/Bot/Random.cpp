
#include <somegames/Bot/Random.hpp>

#include <cassert>

Random::Random() :
  Bot("random"),
  _engine(std::random_device{}())
{}

Position Random::genMove(const Game & g) {
  std::vector<Position> moves = setToVector(g.getMoves());
  const int n = moves.size();
  assert(n>0);
  std::uniform_int_distribution<int> dist(0, n-1);
  const int i = dist(_engine);
  return moves[i];
}

