#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

enum class Status { RedPlay, BluePlay, RedWin, BlueWin, Draw };

enum class Cell { Empty, Red, Blue };

using Position = std::pair<int, int>;

void operator+=(Position & p1, const Position & p2);
void operator-=(Position & p1, const Position & p2);
Position operator-(const Position & p);
Position operator-(const Position & p1, const Position & p2);
Position operator+(const Position & p1, const Position & p2);

using PosSet = std::set<Position>;
using PosVec = std::vector<Position>;

class Game {

  protected:
    Status _status;
    std::string _name;
    std::vector<Position> _history;

    PosSet _moves;
    PosSet _redPositions;
    PosSet _bluePositions;

  public:
    Game(const std::string & name);
    virtual ~Game() = default;
    Status getStatus() const;
    bool isRunning() const;
    const std::string & getName() const;
    const std::vector<Position> & getHistory() const;
    const PosSet & getMoves() const;
    const PosSet & getRedPositions() const;
    const PosSet & getBluePositions() const;

    PosVec getRedPosVec() const;
    PosVec getBluePosVec() const;

    // update _history then call doPlay() or doReset()
    bool play(const Position & p);
    void reset();

  // to be overriden
  public:
    virtual Cell getCell(const Position & p) const = 0;
    virtual Position getSize() const = 0;
    virtual std::unique_ptr<Game> clone() const = 0;

  protected:
    virtual bool doPlay(const Position & p) = 0;
    virtual void doReset() = 0;

};

