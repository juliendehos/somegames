
#include <somegames/somegames.hpp>

#include <iostream>

int main0() {
  Connectfour cf;
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 7}); cf.play({0, 6}); cf.play({0, 5}); cf.play({0, 4}); cf.play({0, 3}); cf.play({0, 2}); cf.play({0, 1}); cf.play({0, 0}); 
  cf.play({0, 7}); cf.play({0, 6}); cf.play({0, 5}); cf.play({0, 4}); cf.play({0, 3}); cf.play({0, 2}); cf.play({0, 1}); cf.play({0, 0}); 
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 6}); cf.play({0, 0}); 
  cf.play({0, 0}); 
  cf.play({0, 1});
  return 0;
}

int main1() {
  Tictactoe g;
  g.play({1, 1}); g.play({0, 0});
  g.play({1, 0});

  GameData gd = mkGameData(g);

  std::cout << std::endl;
  exportTxt(std::cout, gd);
  std::cout << std::endl;
  exportJson(std::cout, gd);
  std::cout << std::endl;

  return 0;
}

int main() {
  Gomoku<9,11> g;

  Position p1 {1, 2};
  p1 += {3, 4};
  const auto [i1, j1] = p1;
  std::cout << i1 << " " << j1 << std::endl;
  // 4 6

  Position p2(-p1);
  const auto [i2, j2] = p2;
  std::cout << i2 << " " << j2 << std::endl;
  // -4 -6

  return 0;
}

