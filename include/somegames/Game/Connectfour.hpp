#pragma once

#include "Game.hpp"

#include <array>

class Connectfour : public Game {
  protected:
    static const int _ni = 8;
    static const int _nj = 8;
    std::array<Cell, _ni*_nj> _board;

  public:
    Connectfour();

    Cell getCell(const Position & p) const override;
    Position getSize() const override;
    std::unique_ptr<Game> clone() const override;

  protected:
    void doReset() override;
    bool doPlay(const Position & p) override;

  protected:
    bool isValid(const Position & p) const;
    int pToK(const Position & p) const;
    Position dropPosition(const Position & p) const;
    int countConnection(const Position & p, const Cell c, const Position & delta) const;
    bool checkConnection(const Position & p, const Cell c, const Position & delta) const;
    void updateMoves();
};


