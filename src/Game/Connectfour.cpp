
#include <somegames/Game/Connectfour.hpp>

Connectfour::Connectfour() : Game("connect four") {
  reset();
}

void Connectfour::doReset() {
  _status = Status::RedPlay;
  _board.fill(Cell::Empty);
  updateMoves();
  _redPositions.clear();
  _bluePositions.clear();
}

Cell Connectfour::getCell(const Position & p) const {
  if (isValid(p)) {
    const int k = pToK(p);
    return _board[k];
  }
  return Cell::Empty;
}

Position Connectfour::getSize() const {
  return {_ni, _nj};
}

bool Connectfour::isValid(const Position & p) const {
  const auto [i, j] = p;
  return i >= 0 and i < _ni and j >= 0 and j < _nj;
}

int Connectfour::pToK(const Position & p) const {
  const auto [i, j] = p;
  return i*_nj + j;
}

Position Connectfour::dropPosition(const Position & p) const {
  const auto [i, j] = p;
  int i1 = _ni-1;
  while (i1 >= 0) {
    const int k = pToK({i1, j});
    if (_board[k] != Cell::Empty)
      break;
    i1--;
  }
  return {i1+1, j};
}

bool Connectfour::doPlay(const Position & p) {
  if (not isRunning()) 
    return false;

  const auto p1 = dropPosition(p);
  if (not isValid(p1))
    return false;

  const int k1 = pToK(p1);
  const auto c1 = _status == Status::RedPlay ? Cell::Red : Cell::Blue;
  _board[k1] = c1;
  updateMoves();

  // update positions
  if (_status == Status::RedPlay)
    _redPositions.insert(p1);
  else if (_status == Status::BluePlay)
    _bluePositions.insert(p1);

  // update status
  if (checkConnection(p1, c1, {0, 1}) or
      checkConnection(p1, c1, {1, 0}) or
      checkConnection(p1, c1, {1, 1}) or
      checkConnection(p1, c1, {1, -1})) 
    _status = _status == Status::RedPlay ? Status::RedWin : Status::BlueWin;
  else if (_moves.empty())
    _status = Status::Draw;
  else if (_status == Status::RedPlay)
    _status = Status::BluePlay;
  else
    _status = Status::RedPlay;

  return true;
}

int Connectfour::countConnection(const Position & p, const Cell c, const Position & delta) const {
  int len = 0;
  Position pp = p;
  pp += delta;
  while (isValid(pp)) {
    const int k = pToK(pp);
    if (_board[k] != c)
      break;
    len++;
    pp += delta;
  }
  return len;
}

bool Connectfour::checkConnection(const Position & p, const Cell c, const Position & delta) const {
  const int len1 = countConnection(p, c, delta);
  const int len2 = countConnection(p, c, -delta);
  const int fullLength = 1 + len1 + len2;
  return fullLength >= 4;
}

std::unique_ptr<Game> Connectfour::clone() const {
  return std::make_unique<Connectfour>(*this);
}

void Connectfour::updateMoves() {
  _moves.clear();
  const int ii = _ni - 1;
  for (int j=0; j<_nj; j++) {
    const int k = pToK({ii, j});
    if (_board[k] == Cell::Empty)
      _moves.insert({ii, j});
  }
}

