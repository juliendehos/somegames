
#include <somegames/Game/Tictactoe.hpp>

#include <catch2/catch.hpp>

const std::set<Position> moves0 {
  {0, 0}, {0, 1}, {0, 2},
  {1, 0}, {1, 1}, {1, 2},
  {2, 0}, {2, 1}, {2, 2}
};

TEST_CASE( "Tictactoe, init" ) {
  Tictactoe t;
  REQUIRE( t.getName() == "tictactoe" );
  REQUIRE( t.getStatus() == Status::RedPlay );
  REQUIRE( t.isRunning() == true );
  REQUIRE( t.getMoves() == moves0 );
  REQUIRE( t.getHistory() == std::vector<Position>() );
}

TEST_CASE( "Tictactoe, play" ) {
  Tictactoe t;
  bool ok = t.play({1,0});
  REQUIRE( ok );
  REQUIRE( t.getStatus() == Status::BluePlay );
  REQUIRE( t.isRunning() == true );
  REQUIRE( t.getHistory() == std::vector<Position>{{1,0}} );
}

TEST_CASE( "Tictactoe, blue cannot capture red" ) {
  Tictactoe t;
  t.play({1,0});
  REQUIRE( t.play({1,0}) == false );
}

TEST_CASE( "Tictactoe, red cannot capture red" ) {
  Tictactoe t;
  t.play({1,0});
  t.play({0,1});
  REQUIRE( t.play({1,0}) == false );
  REQUIRE( t.getHistory() == std::vector<Position>{{1,0}, {0,1}} );

  auto moves = moves0;
  moves.erase({1,0});
  moves.erase({0,1});
  REQUIRE( t.getMoves() == moves );
}

TEST_CASE( "Tictactoe, red win row 1" ) {
  Tictactoe t;
  t.play({1,0}); t.play({0,1});
  t.play({1,1}); t.play({0,0});
  t.play({1,2}); 
  REQUIRE( t.getStatus() == Status::RedWin );
  REQUIRE( t.isRunning() == false );
  REQUIRE( t.play({2,2}) == false );
  REQUIRE( t.getHistory() == std::vector<Position>{{1,0}, {0,1}, {1,1}, {0,0}, {1,2}} );
  REQUIRE( t.getMoves() == std::set<Position>{{0, 2}, {2, 0}, {2, 1}, {2, 2}} );
}

TEST_CASE( "Tictactoe, blue win col 2" ) {
  Tictactoe t;
  t.play({1,1}); t.play({0,2});
  t.play({0,0}); t.play({2,2});
  t.play({1,0}); t.play({1,2});
  REQUIRE( t.getStatus() == Status::BlueWin );
  REQUIRE( t.isRunning() == false );
}

TEST_CASE( "Tictactoe, red win diag 1" ) {
  Tictactoe t;
  t.play({0,0}); t.play({2,0});
  t.play({1,1}); t.play({0,2});
  t.play({2,2});
  REQUIRE( t.getStatus() == Status::RedWin );
  REQUIRE( t.isRunning() == false );
}

TEST_CASE( "Tictactoe, blue win diag 2" ) {
  Tictactoe t;
  t.play({0,1}); t.play({0,2});
  t.play({2,1}); t.play({1,1});
  t.play({2,2}); t.play({2,0});
  REQUIRE( t.getStatus() == Status::BlueWin );
  REQUIRE( t.isRunning() == false );
}

TEST_CASE( "Tictactoe, draw" ) {
  Tictactoe t;
  t.play({1,1}); t.play({0,0});
  t.play({2,0}); t.play({0,2});
  t.play({0,1}); t.play({2,1});
  t.play({1,0}); t.play({1,2});
  t.play({2,2}); 
  REQUIRE( t.getStatus() == Status::Draw );
  REQUIRE( t.isRunning() == false );
}

TEST_CASE( "Tictactoe, red win last move" ) {
  Tictactoe t;
  t.play({1,1}); t.play({0,0});
  t.play({2,0}); t.play({0,2});
  t.play({0,1}); t.play({2,1});
  t.play({1,0}); t.play({2,2});
  t.play({1,2}); 
  REQUIRE( t.getStatus() == Status::RedWin );
  REQUIRE( t.isRunning() == false );
}

