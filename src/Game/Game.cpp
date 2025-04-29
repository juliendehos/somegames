
#include <somegames/Game/Game.hpp>

Game::Game(const std::string & name) : _name(name) {
}

Status Game::getStatus() const {
  return _status;
}

bool Game::isRunning() const {
  return _status == Status::RedPlay or _status == Status::BluePlay;
}

const std::string & Game::getName() const {
  return _name;
}

const std::vector<Position> & Game::getHistory() const {
  return _history;
}

bool Game::play(const Position & p) {
  bool ok = doPlay(p);
  if (ok)
    _history.push_back(p);
  return ok;
}

void Game::reset() {
  _history.clear();
  doReset();
}

const PosSet & Game::getRedPositions() const {
  return _redPositions;
}

const PosSet & Game::getBluePositions() const {
  return _bluePositions;
}

const PosSet & Game::getMoves() const {
  return _moves;
}

void operator+=(Position & p1, const Position & p2) {
  auto &[i1, j1] = p1;
  const auto [i2, j2] = p2;
  i1 += i2;
  j1 += j2;
}

void operator-=(Position & p1, const Position & p2) {
  auto &[i1, j1] = p1;
  const auto [i2, j2] = p2;
  i1 -= i2;
  j1 -= j2;
}

Position operator-(const Position & p) {
  const auto [i, j] = p;
  return {-i, -j};
}

Position operator-(const Position & p1, const Position & p2) {
  const auto [i1, j1] = p1;
  const auto [i2, j2] = p2;
  return {i1-i2, j1-j2};
}

Position operator+(const Position & p1, const Position & p2) {
  const auto [i1, j1] = p1;
  const auto [i2, j2] = p2;
  return {i1+i2, j1+j2};
}

PosVec Game::getRedPosVec() const {
  return PosVec(_redPositions.begin(), _redPositions.end()); 
}

PosVec Game::getBluePosVec() const {
  return PosVec(_bluePositions.begin(), _bluePositions.end()); 
}


