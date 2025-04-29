
#include <somegames/Game/Connectfour.hpp>

#include <catch2/catch.hpp>

class ConnectfourTest : public Connectfour {
  public:
    bool isValid(const Position & p) const {
      return Connectfour::isValid(p);
    }

    int pToK(const Position & p) const {
      return Connectfour::pToK(p);
    }

    Position dropPosition(const Position & p) const {
      return Connectfour::dropPosition(p);
    }

    int countConnection(const Position & p, const Cell c, const Position & delta) const {
      return Connectfour::countConnection(p, c, delta);
    }

    bool checkConnection(const Position & p, const Cell c, const Position & delta) const {
      return Connectfour::checkConnection(p, c, delta);
    }
};

const std::set<Position> moves0 {{7,0}, {7,1}, {7,2}, {7,3}, {7,4}, {7,5}, {7,6}, {7,7}};

TEST_CASE( "ConnectfourTest, init" ) {
  ConnectfourTest cft;
  REQUIRE( cft.getName() == "connect four" );
  REQUIRE( cft.getStatus() == Status::RedPlay );
  REQUIRE( cft.isRunning() == true );
  REQUIRE( cft.getSize() == Position {8, 8} );
  REQUIRE( cft.getMoves() == moves0 );
  REQUIRE( cft.getHistory() == std::vector<Position>{} );
}

TEST_CASE( "ConnectfourTest, play one valid move" ) {
  ConnectfourTest cft;
  bool res = cft.play({2, 3});
  REQUIRE( res == true );
  REQUIRE( cft.getStatus() == Status::BluePlay );
  REQUIRE( cft.isRunning() == true );
  REQUIRE( cft.getMoves() == moves0 );
  REQUIRE( cft.getHistory() == std::vector<Position>{{2,3}} );
}

TEST_CASE( "ConnectfourTest, reset" ) {
  ConnectfourTest cft;
  cft.play({2, 3});
  cft.reset();
  REQUIRE( cft.getStatus() == Status::RedPlay );
  REQUIRE( cft.isRunning() == true );
  REQUIRE( cft.getMoves() == moves0 );
  REQUIRE( cft.getHistory() == std::vector<Position>{} );
}

TEST_CASE( "ConnectfourTest, play one invalid move" ) {
  ConnectfourTest cft;
  bool res = cft.play({2, 42});
  REQUIRE( res == false );
  REQUIRE( cft.getStatus() == Status::RedPlay );
  REQUIRE( cft.isRunning() == true );
  REQUIRE( cft.getMoves() == moves0 );
  REQUIRE( cft.getHistory() == std::vector<Position>{} );
}

TEST_CASE( "ConnectfourTest, isValid" ) {
  ConnectfourTest cft;
  REQUIRE( cft.isValid({ 0, 0}) == true );
  REQUIRE( cft.isValid({ 7, 7}) == true );
  REQUIRE( cft.isValid({ 8, 7}) == false );
  REQUIRE( cft.isValid({-1, 7}) == false );
}

TEST_CASE( "ConnectfourTest, pToK" ) {
  ConnectfourTest cft;
  REQUIRE( cft.pToK({0, 4}) == 4 );
  REQUIRE( cft.pToK({2, 4}) == 20 );
}

// ........
// ........
// ........
// ........
// ........
// ........
// .BBB....
// .RRRR...
TEST_CASE( "Connectfour, play, red win row" ) {
  Connectfour cf;
  cf.play({0, 1}); cf.play({0, 1});
  cf.play({0, 2}); cf.play({0, 2});
  cf.play({0, 3}); cf.play({0, 3});
  cf.play({0, 4}); 
  std::vector<Position> history {{0,1}, {0,1}, {0,2}, {0,2}, {0,3}, {0,3}, {0,4}};
  REQUIRE( cf.getStatus() == Status::RedWin );
  REQUIRE( cf.isRunning() == false );
  REQUIRE( cf.getHistory() == history );
}

// ........
// ........
// ........
// ........
// ........
// ........
// .BBB....
// .RRRR...
TEST_CASE( "Connectfour, play, red win row unordered" ) {
  Connectfour cf;
  cf.play({0, 1}); cf.play({0, 1});
  cf.play({0, 3}); cf.play({0, 3});
  cf.play({0, 2}); cf.play({0, 2});
  cf.play({0, 4}); 
  REQUIRE( cf.getStatus() == Status::RedWin );
  REQUIRE( cf.isRunning() == false );
}

// ........
// ........
// ........
// ........
// ........
// ........
// ..RRR...
// .RBBBB..
TEST_CASE( "Connectfour, play, blue win row" ) {
  Connectfour cf;
  cf.play({0, 1}); cf.play({0, 2});
  cf.play({0, 2}); cf.play({0, 3});
  cf.play({0, 3}); cf.play({0, 4});
  cf.play({0, 4}); cf.play({0, 5});
  REQUIRE( cf.getStatus() == Status::BlueWin );
  REQUIRE( cf.isRunning() == false );
}

// ........
// ........
// ........
// ........
// .R......
// .RB.....
// .RB.....
// .RB.....
TEST_CASE( "Connectfour, play, red win col" ) {
  Connectfour cf;
  cf.play({0, 1}); cf.play({0, 2});
  cf.play({0, 1}); cf.play({0, 2});
  cf.play({0, 1}); cf.play({0, 2});
  cf.play({0, 1}); 
  REQUIRE( cf.getStatus() == Status::RedWin );
  REQUIRE( cf.isRunning() == false );
}

// ........
// ........
// ........
// ........
// ....R...
// ...RB...
// ..RBB...
// .RBBRR..
TEST_CASE( "Connectfour, play, red win diag1" ) {
  Connectfour cf;
  cf.play({0, 1}); cf.play({0, 2});
  cf.play({0, 2}); cf.play({0, 3});
  cf.play({0, 4}); cf.play({0, 3});
  cf.play({0, 3}); cf.play({0, 4});
  cf.play({0, 5}); cf.play({0, 4});
  cf.play({0, 4}); 
  REQUIRE( cf.getStatus() == Status::RedWin );
  REQUIRE( cf.isRunning() == false );
}

// ........
// ........
// ........
// ........
// .R......
// .BR.....
// .BBRB...
// .RRBR...
TEST_CASE( "Connectfour, play, red win diag2" ) {
  Connectfour cf;
  cf.play({3, 1}); cf.play({4, 1});
  cf.play({3, 2}); cf.play({4, 1});
  cf.play({3, 1}); cf.play({4, 2});
  cf.play({3, 2}); cf.play({4, 3});
  cf.play({3, 4}); cf.play({4, 4});
  cf.play({3, 3}); 
  REQUIRE( cf.getStatus() == Status::RedWin );
  REQUIRE( cf.isRunning() == false );
}

// RBRBRBRB
// RBRBRBRB
// BRBRBRBR
// BRBRBRBR
// BRBRBRBR
// RBRBRBRB
// RBRBRBRB
// RBRBRBRB
TEST_CASE( "Connectfour, play, draw" ) {
  Connectfour cf;
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 7}); cf.play({0, 6}); cf.play({0, 5}); cf.play({0, 4}); cf.play({0, 3}); cf.play({0, 2}); cf.play({0, 1}); cf.play({0, 0}); 
  cf.play({0, 7}); cf.play({0, 6}); cf.play({0, 5}); cf.play({0, 4}); cf.play({0, 3}); cf.play({0, 2}); cf.play({0, 1}); cf.play({0, 0}); 
  cf.play({0, 7}); cf.play({0, 6}); cf.play({0, 5}); cf.play({0, 4}); cf.play({0, 3}); cf.play({0, 2}); cf.play({0, 1}); cf.play({0, 0}); 
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  REQUIRE( cf.getStatus() == Status::Draw );
  REQUIRE( cf.isRunning() == false );
  REQUIRE( cf.getMoves() == std::set<Position>() );
}

TEST_CASE( "Connectfour, play, blue win last move" ) {
  Connectfour cf;
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 7}); cf.play({0, 6}); cf.play({0, 5}); cf.play({0, 4}); cf.play({0, 3}); cf.play({0, 2}); cf.play({0, 1}); cf.play({0, 0}); 
  cf.play({0, 7}); cf.play({0, 6}); cf.play({0, 5}); cf.play({0, 4}); cf.play({0, 3}); cf.play({0, 2}); cf.play({0, 1}); cf.play({0, 0}); 
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 5}); cf.play({0, 4}); cf.play({0, 3}); cf.play({0, 2}); cf.play({0, 1}); cf.play({0, 0}); cf.play({0, 0}); cf.play({0, 7}); 
  REQUIRE( cf.getStatus() == Status::BlueWin );
  REQUIRE( cf.isRunning() == false );
}

TEST_CASE( "Connectfour, play, debug 1" ) {
  Connectfour cf;
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 7}); cf.play({0, 6}); cf.play({0, 5}); cf.play({0, 4}); cf.play({0, 3}); cf.play({0, 2}); cf.play({0, 1}); cf.play({0, 0}); 
  cf.play({0, 7}); cf.play({0, 6}); cf.play({0, 5}); cf.play({0, 4}); cf.play({0, 3}); cf.play({0, 2}); cf.play({0, 1}); cf.play({0, 0}); 
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 0}); cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 7}); 
  cf.play({0, 1}); cf.play({0, 2}); cf.play({0, 3}); cf.play({0, 4}); cf.play({0, 5}); cf.play({0, 6}); cf.play({0, 6}); cf.play({0, 0}); 
  cf.play({0, 0}); cf.play({0, 1});
  REQUIRE( cf.getStatus() == Status::RedPlay );
  REQUIRE( cf.isRunning() == true );
}

// .B......
// .R......
// .B......
// .R......
// .B......
// .R......
// .B......
// .R......
TEST_CASE( "Connectfour, getMoves" ) {
  Connectfour cf;
  cf.play({0, 1}); cf.play({0, 1}); 
  cf.play({0, 1}); cf.play({0, 1}); 
  cf.play({0, 1}); cf.play({0, 1}); 
  cf.play({0, 1}); cf.play({0, 1}); 
  std::set<Position> moves {{7,0}, {7,2}, {7,3}, {7,4}, {7,5}, {7,6}, {7,7}};
  std::vector<Position> history {{0,1}, {0,1}, {0,1}, {0,1}, {0,1}, {0,1}, {0,1}, {0,1}};
  REQUIRE( cf.getStatus() == Status::RedPlay );
  REQUIRE( cf.isRunning() == true );
  REQUIRE( cf.getMoves() == moves );
  REQUIRE( cf.getHistory() == history );
}

