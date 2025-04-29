#pragma once

#include "../Game/Game.hpp"
#include "../Bot/Bot.hpp"

#include <memory>

enum class AppError { BadArguments, UnknownUi, UnknownGame, UnknownBot, NoGame, NoBot };

class App {
  protected:
    std::unique_ptr<Game> _pGame;
    std::unique_ptr<Bot> _pBot;

  public:
    App() = default;
    App(std::unique_ptr<Game> && pGame, std::unique_ptr<Bot> && pBot);

    ~App() = default;

    virtual int run() = 0;

    std::string fmtStatus(Status s) const;
};

