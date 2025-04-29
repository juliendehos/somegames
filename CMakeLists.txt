cmake_minimum_required( VERSION 3.20 )
project( somegames )
set( CMAKE_CXX_STANDARD 20 )

include_directories( include )

find_package( OpenMP REQUIRED )

find_package( reflectcpp REQUIRED )

find_package( PkgConfig )
pkg_check_modules( GTKMM_VARS REQUIRED IMPORTED_TARGET gtkmm-4.0 )

add_library( somegames-lib 
  src/App/App.cpp
  src/App/Cli.cpp
  src/App/Gui.cpp
  src/Bot/Bot.cpp
  src/Bot/Human.cpp
  src/Bot/Montecarlo.cpp
  src/Bot/Random.cpp
  src/Export/Export.cpp
  src/Export/Json.cpp
  src/Export/Txt.cpp
  src/Game/Connectfour.cpp
  src/Game/Game.cpp
  src/Game/Reversi.cpp
  src/Game/Tictactoe.cpp
  )
target_link_libraries( somegames-lib 
  PRIVATE reflectcpp PkgConfig::GTKMM_VARS OpenMP::OpenMP_CXX )

add_executable( somegames-app app/main.cpp )
target_link_libraries( somegames-app 
  PRIVATE somegames-lib reflectcpp PkgConfig::GTKMM_VARS OpenMP::OpenMP_CXX )

install( TARGETS somegames-app DESTINATION bin )

add_executable( somegames-debug app/debug.cpp )
target_link_libraries( somegames-debug 
  PRIVATE somegames-lib reflectcpp PkgConfig::GTKMM_VARS OpenMP::OpenMP_CXX )

add_executable( somegames-test
  test/Connectfour-test.cpp 
  test/Gomoku-test.cpp 
  test/Reversi-test.cpp 
  test/Tictactoe-test.cpp 
  test/main.cpp )
target_link_libraries( somegames-test somegames-lib )

enable_testing()
add_test( NAME somegames-test COMMAND somegames-test )

