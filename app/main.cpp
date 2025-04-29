
#include <somegames/somegames.hpp>

#include <iostream>

void usage() {
  std::cerr << "usage: <cli game bot | gui>" << std::endl;
  std::cerr << "  - game: connectfour | tictactoe | gomoku8x8 | gomoku7x9 | reversi" << std::endl;
  std::cerr << "  - bot: human | mc1k | mc100k | random" << std::endl;
}

int main(int argc, char ** argv) {

  try {
    if (argc < 2) throw AppError:: BadArguments;

    std::unique_ptr<App> pUi;
    const std::string uiStr(argv[1]);
    if (uiStr == "cli") {
      if (argc != 4) throw AppError:: BadArguments;
      pUi = std::make_unique<Cli>(argv[2], argv[3]);
    }
    else if (uiStr == "gui"){
      if (argc != 2) throw AppError:: BadArguments;
      pUi = std::make_unique<Gui>();
    }
    else
      throw AppError::UnknownUi;

    return pUi->run();
  }
  catch(const AppError & err) {
    switch(err) {
      case AppError::BadArguments: 
        std::cerr << "Bad arguments" << std::endl;
        break;
      case AppError::UnknownUi: 
        std::cerr << "Unknown ui" << std::endl;
        break;
      case AppError::UnknownGame:
        std::cerr << "Unknown game" << std::endl;
        break;
      case AppError::UnknownBot:
        std::cerr << "Unknown bot" << std::endl;
        break;
    }
    usage();
    return -1;
  }
  catch(...) {
    std::cerr << "Unknown error" << std::endl;
    return -1;
  }

  return 0;
}

