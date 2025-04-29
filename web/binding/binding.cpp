
#include <somegames/Bot/Human.hpp>
#include <somegames/Bot/Montecarlo.hpp>
#include <somegames/Bot/Random.hpp>

#include <somegames/Game/Connectfour.hpp>
#include <somegames/Game/Gomoku.hpp>
#include <somegames/Game/Reversi.hpp>
#include <somegames/Game/Tictactoe.hpp>

#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(somegames) {

  ///////////////////////////////////////////////////////////////////////////////
  // Game
  ///////////////////////////////////////////////////////////////////////////////

  emscripten::enum_<Status>("Status")
    .value("RedPlay", Status::RedPlay)
    .value("BluePlay", Status::BluePlay)
    .value("RedWin", Status::RedWin)
    .value("BlueWin", Status::BlueWin)
    .value("Draw", Status::Draw)
    ;

  emscripten::value_array<std::pair<int,int>>("Position")
    .element(&std::pair<int,int>::first)
    .element(&std::pair<int,int>::second)
    ;

  emscripten::register_vector<Position>("vector<Position>");

  emscripten::class_<Game>("Game")
    .function("getName", &Game::getName)
    .function("getStatus", &Game::getStatus)
    .function("getRedPosVec", &Game::getRedPosVec)
    .function("getBluePosVec", &Game::getBluePosVec)
    .function("play", &Game::play)
    .function("reset", &Game::reset)
    .function("isRunning", &Game::isRunning)
    ;

  ///////////////////////////////////////////////////////////////////////////////
  // Game Connectfour
  ///////////////////////////////////////////////////////////////////////////////

  emscripten::class_<Connectfour, emscripten::base<Game>>("Connectfour")
    .constructor<>()
    .function("getSize", &Connectfour::getSize)
    .function("clone", &Connectfour::clone)
    ;

  ///////////////////////////////////////////////////////////////////////////////
  // Game Gomoku
  ///////////////////////////////////////////////////////////////////////////////

  emscripten::class_<Gomoku<7,9>, emscripten::base<Game>>("Gomoku7x9")
    .constructor<>()
    .function("getSize", &Gomoku<7,9>::getSize)
    .function("clone", &Gomoku<7,9>::clone)
    ;

  emscripten::class_<Gomoku<8,8>, emscripten::base<Game>>("Gomoku8x8")
    .constructor<>()
    .function("getSize", &Gomoku<8,8>::getSize)
    .function("clone", &Gomoku<8,8>::clone)
    ;

  ///////////////////////////////////////////////////////////////////////////////
  // Game Reversi
  ///////////////////////////////////////////////////////////////////////////////

  emscripten::class_<Reversi, emscripten::base<Game>>("Reversi")
    .constructor<>()
    .function("getSize", &Reversi::getSize)
    .function("clone", &Reversi::clone)
    ;

  ///////////////////////////////////////////////////////////////////////////////
  // Game Tictactoe
  ///////////////////////////////////////////////////////////////////////////////

  emscripten::class_<Tictactoe, emscripten::base<Game>>("Tictactoe")
    .constructor<>()
    .function("getSize", &Tictactoe::getSize)
    .function("clone", &Tictactoe::clone)
    ;

  ///////////////////////////////////////////////////////////////////////////////
  // Bot
  ///////////////////////////////////////////////////////////////////////////////

  emscripten::class_<Bot>("Bot")
    .function("isHuman", &Bot::isHuman)
    .function("getName", &Bot::getName)
    ;

  ///////////////////////////////////////////////////////////////////////////////
  // Bot Human
  ///////////////////////////////////////////////////////////////////////////////

  emscripten::class_<Human, emscripten::base<Bot>>("Human")
    .constructor<>()
    .function("genMove", &Human::genMove)
    .function("isHuman", &Human::isHuman)
    ;

  ///////////////////////////////////////////////////////////////////////////////
  // Bot Montecarlo
  ///////////////////////////////////////////////////////////////////////////////

  emscripten::class_<Montecarlo, emscripten::base<Bot>>("Montecarlo")
    .constructor<int>()
    .function("genMove", &Montecarlo::genMove)
    ;

  ///////////////////////////////////////////////////////////////////////////////
  // Bot Random
  ///////////////////////////////////////////////////////////////////////////////

  emscripten::class_<Random, emscripten::base<Bot>>("Random")
    .constructor<>()
    .function("genMove", &Random::genMove)
    ;

}

