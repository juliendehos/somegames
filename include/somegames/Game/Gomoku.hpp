#pragma once

#include "Game.hpp"

template <int NI, int NJ>
class Gomoku : public Game {

  public:
    Gomoku();

    Cell getCell(const Position & p) const override;
    Position getSize() const override;
    std::unique_ptr<Game> clone() const override;

  protected:
    void doReset() override;
    bool doPlay(const Position & p) override;

  private:
    void updateStatus(const PosSet & positions, const Position & p, Status winStatus, Status nextStatus);
    bool checkLine(const PosSet & positions, const Position & p, const Position & delta);
};

template <int NI, int NJ>
Gomoku<NI, NJ>::Gomoku() : 
  Game("gomoku" + std::to_string(NI) + "x" + std::to_string(NJ)) 
{
  reset();
}

template <int NI, int NJ>
void Gomoku<NI, NJ>::doReset() {

  _status = Status::RedPlay;

  _redPositions.clear();
  _bluePositions.clear();

  _moves.clear();
  for (int i=0; i<NI; i++) 
    for (int j=0; j<NJ; j++)
      _moves.insert({i, j});

}

template <int NI, int NJ>
bool Gomoku<NI, NJ>::doPlay(const Position & p) {

  if (not _moves.contains(p))
    return false;

  _moves.erase(p);

  if (_status == Status::RedPlay) {
    _redPositions.insert(p);
    updateStatus(_redPositions, p, Status::RedWin, Status::BluePlay);
  }
  else {
    _bluePositions.insert(p);
    updateStatus(_bluePositions, p, Status::BlueWin, Status::RedPlay);
  }

  return true;
}

template <int NI, int NJ>
void Gomoku<NI, NJ>::updateStatus(
  const PosSet & positions, 
  const Position & p, 
  Status winStatus, 
  Status nextStatus) 
{
  if (checkLine(positions, p, {0, 1}) or
      checkLine(positions, p, {1, 0}) or
      checkLine(positions, p, {1, 1}) or
      checkLine(positions, p, {1, -1}))
    _status = winStatus;
  else if (_moves.empty())
    _status = Status::Draw;
  else
    _status = nextStatus;
}

template <int NI, int NJ>
bool Gomoku<NI, NJ>::checkLine(
  const PosSet & positions, 
  const Position & p, 
  const Position & delta) 
{
  int len = 1;

  for (auto pp=p+delta; positions.contains(pp); pp+=delta)
    len++;

  for (auto pp=p-delta; positions.contains(pp); pp-=delta)
    len++;

  return len >= 5;


  /*
  const auto [i0, j0] = p;

  for (int i=i0+di, j=j0+dj; positions.contains({i,j}); i+=di, j+=dj)
    len++;

  for (int i=i0-di, j=j0-dj; positions.contains({i,j}); i-=di, j-=dj)
    len++;
    */
}

template <int NI, int NJ>
Cell Gomoku<NI, NJ>::getCell(const Position & p) const {
  if (_redPositions.contains(p))
    return Cell::Red;
  else if (_bluePositions.contains(p))
    return Cell::Blue;
  return Cell::Empty;
}

template <int NI, int NJ>
Position Gomoku<NI, NJ>::getSize() const {
  return {NI, NJ};
}

template <int NI, int NJ>
std::unique_ptr<Game> Gomoku<NI, NJ>::clone() const {
  return std::make_unique<Gomoku<NI, NJ>>(*this);
}

