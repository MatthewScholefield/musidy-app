#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/SongGenerator.hpp"


TEST_CASE("Song Generator", "[song-generator]") {
  REQUIRE(SongGenerator::ClosestNote(0, 0) == 0);
  REQUIRE(SongGenerator::ClosestNote(-1, 0) == -1);
  REQUIRE(SongGenerator::ClosestNote(1, 0) == 1);
  REQUIRE(SongGenerator::ClosestNote(0, 7) == 7);
  REQUIRE(SongGenerator::ClosestNote(4, 8) == 11);
}
