
#include <somegames/App/App.hpp>

App::App(std::unique_ptr<Game> && pGame, std::unique_ptr<Bot> && pBot) :
  _pGame(std::move(pGame)),
  _pBot(std::move(pBot))
{}

std::string App::fmtStatus(Status s) const {
  switch(s) {
    case Status::RedPlay:   return "RedPlay";
    case Status::BluePlay:  return "BluePlay";
    case Status::RedWin:    return "RedWin";
    case Status::BlueWin:   return "BlueWin";
    case Status::Draw:      return "Draw";
  }
  return {};
}

