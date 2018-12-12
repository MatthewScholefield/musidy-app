#define CATCH_CONFIG_MAIN

#include "libs/catch.hpp"
#include "../source/songCreation/ScorePlayer.hpp"


TEST_CASE("Song Generator", "[song-generator]") {
    REQUIRE(ScorePlayer::closestNote(0, 0) == 0);
    REQUIRE(ScorePlayer::closestNote(-1, 0) == -1);
    REQUIRE(ScorePlayer::closestNote(1, 0) == 1);
    REQUIRE(ScorePlayer::closestNote(0, 7) == 7);
    REQUIRE(ScorePlayer::closestNote(4, 8) == 11);
}
