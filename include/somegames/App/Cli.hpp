#pragma once

#include "App.hpp"
#include "../Game/Game.hpp"

#include <optional>
#include <string>

class Cli : public App {
  public:
    explicit Cli(const std::string & gameName, const std::string & botName);
    int run() override;

  private:
    void displayGame() const;
    std::optional<Position> parsePosition(const std::string & input) const;
    std::string fmtCell(const Cell & c) const;
    std::string fmtPosition(const Position & p) const;
};

