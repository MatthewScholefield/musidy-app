#include "libs/catch.hpp"
#include "../source/utils.hpp"

TEST_CASE("selectSample", "[select-sample]") {
    SECTION("") REQUIRE(selectSample({0.f, 0.f, 2.f}) == 2);
    SECTION("") REQUIRE(selectSample({0.f, 3.f, 0.f}) == 1);
    SECTION("") REQUIRE(selectSample({0.1f, 0.f, 0.f}) == 0);
    SECTION("") REQUIRE(selectSample({100.f}) == 0);
}

TEST_CASE("randFloat", "[rand-float]") {
    SECTION("") REQUIRE(randFloat() <= 1.f);
    SECTION("") REQUIRE(randFloat() <= 1.f);
    SECTION("") REQUIRE(randFloat() <= 1.f);
    SECTION("") REQUIRE(randFloat() >= 0.f);
    SECTION("") REQUIRE(randFloat() >= 0.f);
    SECTION("") REQUIRE(randFloat() >= 0.f);
}

TEST_CASE("min", "[min]") {
    SECTION("") REQUIRE(min(12, 10, 15) == 10);
    SECTION("") REQUIRE(min(12, 2, 4, 6, 22, 23, 24) == 2);
    SECTION("") REQUIRE(min(12, 9, 14) == 9);
    SECTION("") REQUIRE(min(10, 10) == 10);
}

TEST_CASE("minTo", "[min-to]") {
    SECTION("") REQUIRE(minTo(12, 10, 15) == 10);
    SECTION("") REQUIRE(minTo(12, 2, 4, 6, 22, 23, 24) == 6);
    SECTION("") REQUIRE(minTo(12, 9, 14) == 14);
    SECTION("") REQUIRE(minTo(10, 10, 12) == 10);
    SECTION("") REQUIRE(minTo(18, 0, 17) == 17);
}
