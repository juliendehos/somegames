cmake_minimum_required( VERSION 3.20 )
project( somegames-web )
set( CMAKE_CXX_STANDARD 20 )

include_directories( ../include )

add_executable( somegames-web 

  binding/binding.cpp

  ../src/Bot/Bot.cpp
  ../src/Bot/Human.cpp
  ../src/Bot/Random.cpp
  ../src/Bot/Montecarlo.cpp

  ../src/Game/Connectfour.cpp
  ../src/Game/Game.cpp
  ../src/Game/Reversi.cpp
  ../src/Game/Tictactoe.cpp
)

set_target_properties( somegames-web PROPERTIES COMPILE_FLAGS "-O2" )
set_target_properties( somegames-web PROPERTIES LINK_FLAGS    "-O2 --bind" )

# set_target_properties( somegames-web PROPERTIES LINK_FLAGS    "-s WASM=1 --bind" )

