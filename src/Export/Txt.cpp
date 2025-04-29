
#include <somegames/Export/Txt.hpp>

std::string fmtStatus(Status s) {
  switch (s) {
    case Status::RedPlay:   return "red play";
    case Status::BluePlay:  return "blue play";
    case Status::RedWin:    return "red win";
    case Status::BlueWin:   return "blue win";
    case Status::Draw:      return "draw";
  }
  return {};
}

std::string fmtPosition(const Position & p) {
  const auto [i, j] = p;
  return std::to_string(i) + "," + std::to_string(j);
}

void exportTxt(std::ostream & os, const GameData & gd) {

  os << gd.name << std::endl;

  os << fmtStatus(gd.status) << std::endl;

  for (const auto & p : gd.red_positions)
    os << fmtPosition(p) << ";";
  os << std::endl;

  for (const auto & p : gd.blue_positions)
    os << fmtPosition(p) << ";";
  os << std::endl;

  for (const auto & p : gd.history)
    os << fmtPosition(p) << ";";
  os << std::endl;

}


