
#include <somegames/Game/Reversi.hpp>

Reversi::Reversi() : Game("reversi") {
  reset();
}

void Reversi::doReset() {

  _board.fill(Cell::Empty);
  _board[pToK({3, 3})] = Cell::Red;
  _board[pToK({4, 4})] = Cell::Red;
  _board[pToK({3, 4})] = Cell::Blue;
  _board[pToK({4, 3})] = Cell::Blue;

  _redPositions = {{3, 3}, {4, 4}};

  _bluePositions = {{3, 4}, {4, 3}};

  updateMoves(Cell::Blue, _redPositions);

  _status = Status::RedPlay;
}

bool Reversi::doPlay(const Position & p) {

  // TODO FIXME no move but not terminated

  if (not _moves.contains(p))
    return false;

  using ccpps_t = std::tuple<const Cell, const Cell, PosSet &, PosSet &, const Status>;
  auto [curCell, oppCell, curPos, oppPos, nextStatus] = 
    _status == Status::RedPlay ? 
       ccpps_t {Cell::Red, Cell::Blue, _redPositions, _bluePositions, Status::BluePlay} :
       ccpps_t {Cell::Blue, Cell::Red, _bluePositions, _redPositions, Status::RedPlay} ;

  updatePos(curCell, curPos, oppPos, p);

  // update for next play
  updateMoves(curCell, oppPos);

  // update status
  if (_moves.empty()) {
    const int nRed = _redPositions.size();
    const int nBlue = _bluePositions.size();

    // next player cannot play
    if (nRed+nBlue < _ni*_nj) {
      // try current player plays again
      updateMoves(oppCell, curPos);
      if (not _moves.empty())
        return true;
    }

    if (nRed > nBlue)
      _status = Status::RedWin;
    else if (nRed < nBlue)
      _status = Status::BlueWin;
    else
      _status = Status::Draw;
  }
  else
    _status = nextStatus;

  return true;
}

Cell Reversi::getCell(const Position & p) const {
  if (isValid(p)) {
    const int k = pToK(p);
    return _board[k];
  }
  return Cell::Empty;
}

Position Reversi::getSize() const {
  return {_ni, _nj};
}

std::unique_ptr<Game> Reversi::clone() const {
  return std::make_unique<Reversi>(*this);
}

bool Reversi::isValid(const Position & p) const {
  const auto [i, j] = p;
  return i >= 0 and i < _ni and j >= 0 and j < _nj;
}

int Reversi::pToK(const Position & p) const {
  const auto [i, j] = p;
  return i*_nj + j;
}

void Reversi::updatePos(
    const Cell curCell, 
    PosSet & curPos, 
    PosSet & oppPos, 
    const Position & p)
{
  // new position
  _board[pToK(p)] = curCell;
  curPos.insert(p);

  // captured positions
  for (const Position & pp : _captures[p]) {
    _board[pToK(pp)] = curCell;
    curPos.insert(pp);
    oppPos.erase(pp);
  }

}

void Reversi::updateMoves(const Cell oppCell, const PosSet & curPos) {
  _moves.clear();
  _captures.clear();
  for (const Position & p : curPos) {
    updateMovesLine(oppCell, p, { 0,  1});
    updateMovesLine(oppCell, p, { 0, -1});
    updateMovesLine(oppCell, p, { 1,  0});
    updateMovesLine(oppCell, p, {-1,  0});
    updateMovesLine(oppCell, p, { 1,  1});
    updateMovesLine(oppCell, p, {-1, -1});
    updateMovesLine(oppCell, p, { 1, -1});
    updateMovesLine(oppCell, p, {-1,  1});
  }
}

void Reversi::updateMovesLine(const Cell oppCell, const Position & p, const Position & delta) {

  Position pp = p + delta;
  Cell cc = _board[pToK(pp)];
  PosSet capturedPos {pp};

  // the next position should be occupied by the opponent
  if (cc != oppCell)
    return;

  // store positions while they are occupied by the opponent
  while (true) {
    pp += delta;
    if (not isValid(pp))
      return;
    cc = _board[pToK(pp)];
    if (cc != oppCell)
      break;
    capturedPos.insert(pp);
  }

  // if the following position is empty, we can capture these positions
  if (cc == Cell::Empty) {
    _moves.insert(pp);

    if (_captures.contains(pp))
      _captures[pp].merge(capturedPos);
    else
      _captures[pp] = capturedPos;
  }
}


