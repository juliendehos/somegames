
#include <somegames/Bot/Human.hpp>

#include <cassert>

Human::Human() : Bot("human") {}

Position Human::genMove(const Game & g) {
  assert(false);
  return {};
}

bool Human::isHuman() const {
  return true;
}

