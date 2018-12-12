#include "libs/catch.hpp"
#include "../source/songCreation/noteUtils.hpp"


TEST_CASE("closestNote", "[closest-note]") {
    SECTION("") REQUIRE(closestNote(0, 0) == 0);
    SECTION("") REQUIRE(closestNote(-1, 0) == -1);
    SECTION("") REQUIRE(closestNote(1, 0) == 1);
    SECTION("") REQUIRE(closestNote(0, 7) == 7);
    SECTION("") REQUIRE(closestNote(4, 8) == 11);
}

TEST_CASE("upperNoteTo", "[upper-note-to]") {
    SECTION("") REQUIRE(upperNoteTo(12, 3) == 17);
    SECTION("") REQUIRE(upperNoteTo(16, 3) == 17);
    SECTION("") REQUIRE(upperNoteTo(17, 3) == 17);
    SECTION("") REQUIRE(upperNoteTo(18, 3) == 24);
}

TEST_CASE("lowerNoteTo", "[lower-note-to]") {
    SECTION("") REQUIRE(lowerNoteTo(12, 3) == 10);
    SECTION("") REQUIRE(lowerNoteTo(16, 3) == 10);
    SECTION("") REQUIRE(lowerNoteTo(17, 3) == 17);
    SECTION("") REQUIRE(lowerNoteTo(18, 3) == 17);
}
