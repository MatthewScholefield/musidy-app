#define CATCH_CONFIG_MAIN

#include "libs/catch.hpp"
#include "../source/songCreation/noteUtils.hpp"


TEST_CASE("Song Generator", "[song-generator]") {
    REQUIRE(closestNote(0, 0) == 0);
    REQUIRE(closestNote(-1, 0) == -1);
    REQUIRE(closestNote(1, 0) == 1);
    REQUIRE(closestNote(0, 7) == 7);
    REQUIRE(closestNote(4, 8) == 11);
}
