#pragma once

#include "Game.hpp"

#include <array>
#include <map>

class Reversi : public Game {
  protected:
    static const int _ni = 8;
    static const int _nj = 8;

    std::array<Cell, _ni*_nj> _board;

    std::map<Position,PosSet> _captures;  // positions captured by each moves 

  public:
    Reversi();

    Cell getCell(const Position & p) const override;
    Position getSize() const override;
    std::unique_ptr<Game> clone() const override;

  protected:
    void doReset() override;
    bool doPlay(const Position & p) override;

  protected:
    bool isValid(const Position & p) const;
    int pToK(const Position & p) const;

    void updatePos(
        const Cell curCell, 
        PosSet & curPos, 
        PosSet & oppPos, 
        const Position & p);

    void updateMoves(const Cell oppCell, const PosSet & curPos);

    void updateMovesLine(const Cell oppCell, const Position & p, const Position & delta);

};


