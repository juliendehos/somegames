
#include <rfl/json.hpp>
#include <rfl.hpp>

#include <somegames/Export/Json.hpp>

void exportJson(std::ostream & os, const GameData & gd) {
  os << rfl::json::write(gd);
}

