
#include <somegames/Game/Tictactoe.hpp>

#include <cassert>

Tictactoe::Tictactoe() : Game("tictactoe") {
  assert(_ni == _nj);
  reset();
}

void Tictactoe::doReset() {

  _status = Status::RedPlay;
  _redPositions.clear();
  _bluePositions.clear();

  _moves.clear();
  for (int i=0; i<_ni; i++) 
    for (int j=0; j<_nj; j++)
      _moves.insert({i, j});

}

bool Tictactoe::isValid(const Position & p) const {
  const auto [i,j] = p;
  return i >= 0 and i < _ni and j >= 0 and j < _nj;
}

bool Tictactoe::checkWin(const Position & p, const PosSet & pos) const {
  auto [i,j] = p;
  bool search;

  // check row
  search = true;
  for (int jj=0; jj<_nj and search; jj++)
    if (not pos.contains({i, jj}))
      search = false;
  if (search)
    return true;

  // check col
  search = true;
  for (int ii=0; ii<_ni and search; ii++)
    if (not pos.contains({ii, j}))
      search = false;
  if (search)
    return true;

  // check diag1
  search = true;
  for (int k=0; k<_ni and search; k++)
    if (not pos.contains({k, k}))
      search = false;
  if (search)
    return true;

  // check diag2
  search = true;
  for (int k=0; k<_ni and search; k++)
    if (not pos.contains({k, _ni-1-k}))
      search = false;
  if (search)
    return true;

  return false;
}

bool Tictactoe::update(const Position & p, 
    PosSet & pos1, 
    const PosSet & pos2,
    Status playStatus,
    Status winStatus) {

  if (not isValid(p) or pos1.contains(p) or pos2.contains(p))
    return false;

  pos1.insert(p);
  _moves.erase(p);

  if (checkWin(p, pos1))
    _status = winStatus;
  else if (_moves.empty())
    _status = Status::Draw;
  else
    _status = playStatus;

  return true;
}

bool Tictactoe::doPlay(const Position & p) {

  if (_status == Status::RedPlay)
    return update(p, _redPositions, _bluePositions, Status::BluePlay, Status::RedWin);

  if (_status == Status::BluePlay)
    return update(p, _bluePositions, _redPositions, Status::RedPlay, Status::BlueWin);

  return false;
}

Cell Tictactoe::getCell(const Position & p) const {
  if (_redPositions.contains(p))
    return Cell::Red;
  else if (_bluePositions.contains(p))
    return Cell::Blue;
  else
    return Cell::Empty;
}

Position Tictactoe::getSize() const {
  return {_ni, _nj};
}

std::unique_ptr<Game> Tictactoe::clone() const {
  return std::make_unique<Tictactoe>(*this);
}


