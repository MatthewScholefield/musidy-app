#define CATCH_CONFIG_MAIN
#include "libs/catch.hpp"
#include "../source/SongGenerator.hpp"


TEST_CASE("Song Generator", "[song-generator]") {
  REQUIRE(SongGenerator::closestNote(0, 0) == 0);
  REQUIRE(SongGenerator::closestNote(-1, 0) == -1);
  REQUIRE(SongGenerator::closestNote(1, 0) == 1);
  REQUIRE(SongGenerator::closestNote(0, 7) == 7);
  REQUIRE(SongGenerator::closestNote(4, 8) == 11);
}
