
#include <somegames/somegames.hpp>

#include <iostream>
#include <sstream>

Cli::Cli(const std::string & gameName, const std::string & botName) {
  if (gameName == "tictactoe")
    _pGame = std::make_unique<Tictactoe>();
  else if (gameName == "connectfour")
    _pGame = std::make_unique<Connectfour>();
  else if (gameName == "gomoku8x8")
    _pGame = std::make_unique<Gomoku<8,8>>();
  else if (gameName == "gomoku7x9")
    _pGame = std::make_unique<Gomoku<7,9>>();
  else if (gameName == "reversi")
    _pGame = std::make_unique<Reversi>();
  else
    throw AppError::UnknownGame;

  if (botName == "random")
    _pBot = std::make_unique<Random>();
  else if (botName == "mc1k")
    _pBot = std::make_unique<Montecarlo>(1000);
  else if (botName == "mc100k")
    _pBot = std::make_unique<Montecarlo>(100000);
  else if (botName == "human")
    _pBot = std::make_unique<Human>();
  else
    throw AppError::UnknownBot;

}

int Cli::run() {
  if (not _pGame)
    throw AppError::NoGame;

  if (not _pBot)
    throw AppError::NoBot;

  std::string input;

  displayGame();

  while (_pGame->isRunning()) {

    const Status status = _pGame->getStatus();

    if (status == Status::RedPlay or status == Status::BluePlay and _pBot->isHuman()) {

      std::cout << "action (i j)? ";
      std::flush(std::cout);

      std::getline(std::cin, input);
      if (input.empty())
        return 0;

      const auto p = parsePosition(input);
      if (not p)
        std::cout << "invalid input" << std::endl;
      else if (_pGame->play(*p)) {
        std::cout << "played" << std::endl;
        displayGame();
      } else 
        std::cout << "invalid action" << std::endl;
    }
    else {    // BluePlay and not human
      while (_pGame->getStatus() == Status::BluePlay) {
        const Position p = _pBot->genMove(*_pGame);
        _pGame->play(p);
        displayGame();
      }
    }

  }

  return 0;
}

void Cli::displayGame() const {
  if (not _pGame)
    throw AppError::NoGame;

  const auto [ni, nj] = _pGame->getSize();

  std::cout << std::endl;

  for (int i=ni-1; i>=0; i--) {
    std::cout << i << " ";
    for (int j=0; j<nj; j++) {
      const Cell c = _pGame->getCell({i,j});
      std::cout << fmtCell(c);
    }
    std::cout << std::endl;
  }

  std::cout << "  ";
  for (int i=0; i<ni; i++)
    std::cout << i;
  std::cout << std::endl;

  const Status s = _pGame->getStatus();
  std::cout << "status: " << fmtStatus(s) << std::endl;

  std::cout << "history: ";
  for (const Position & p : _pGame->getHistory())
    std::cout << fmtPosition(p) << "; ";
  std::cout << std::endl;
}

std::optional<Position> Cli::parsePosition(const std::string & input) const {
  std::istringstream iss(input);
  try {
    std::string iStr, jStr;
    std::getline(iss, iStr, ' ');
    std::getline(iss, jStr);
    const int i = std::stoi(iStr);
    const int j = std::stoi(jStr);
    return {{i, j}};
  }
  catch(...) {
    return {};
  }
}

std::string Cli::fmtCell(const Cell & c) const {
  switch(c) {
    case Cell::Empty: return ".";
    case Cell::Red:   return "R";
    case Cell::Blue:  return "B";
  }
  return {};
}

std::string Cli::fmtPosition(const Position & p) const {
  const auto [i, j] = p;
  return std::to_string(i) + " " + std::to_string(j);
}

