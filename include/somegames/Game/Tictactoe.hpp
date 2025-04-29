#pragma once

#include "Game.hpp"

class Tictactoe : public Game {
  protected:
    const int _ni = 3;
    const int _nj = 3;

  public:
    Tictactoe();

    Cell getCell(const Position & p) const override;
    Position getSize() const override;
    std::unique_ptr<Game> clone() const override;

  protected:
    void doReset() override;
    bool doPlay(const Position & p) override;

  private:
    bool isValid(const Position & p) const;

    bool checkWin(const Position & p, const PosSet & pos) const;

    bool update(const Position & p, 
        PosSet & pos1, 
        const PosSet & pos2, 
        Status playStatus, 
        Status winStatus);
};


