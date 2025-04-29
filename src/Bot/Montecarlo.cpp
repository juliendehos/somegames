
#include <somegames/Bot/Montecarlo.hpp>

#include <algorithm>
#include <cassert>
#include <limits>

Montecarlo::Montecarlo(int totalSims) :
  Bot("montecarlo" + std::to_string(totalSims)),
  _engine(std::random_device{}()),
  _totalSims(totalSims)
{}

Position Montecarlo::genMove(const Game & g) {
  const std::vector<Position> moves = setToVector(g.getMoves());
  const int nMoves = moves.size();
  assert(nMoves > 0);
  const int nSims = _totalSims / nMoves;

  std::vector<int> scores(nMoves);
#pragma omp parallel for
  for (int i=0; i<nMoves; i++) {
    const Position & p = moves[i];
    scores[i] = evalMove(g, p, nSims);
  }

  auto iterMax = std::max_element(scores.begin(), scores.end());
  const int best = std::distance(scores.begin(), iterMax);
  return moves[best];
}

int Montecarlo::evalMove(const Game & g, const Position & p, int nSims) {

  auto winStatus = Status::BlueWin;
  auto loseStatus = Status::RedWin;
  if (g.getStatus() == Status::RedPlay)
    std::swap(winStatus, loseStatus);

  auto pGame = g.clone();
  pGame->play(p);
  int score = 0;

  for (int i=0; i<nSims; i++) {
    Status s = randomPlayout(*pGame);
    if (s == winStatus)
      score++;
    else if (s == loseStatus)
      score--;
  }

  return score;
}

Status Montecarlo::randomPlayout(const Game & g) {
  auto pGame = g.clone();
  while (pGame->isRunning()) {
    Position p = randomMove(*pGame);
    pGame->play(p);
  }
  return pGame->getStatus();
}

Position Montecarlo::randomMove(const Game & g) {
  std::vector<Position> moves = setToVector(g.getMoves());
  const int n = moves.size();
  assert(n > 0);
  std::uniform_int_distribution<int> dist(0, n-1);
  const int i = dist(_engine);
  return moves[i];
}

