#pragma once

#include "ScorePlayer.hpp"
#include "SongScore.hpp"
#include "../Instrument.hpp"
#include "chordProgressions.hpp"
#include "noteUtils.hpp"

class ScoreGenerator {
public:
    explicit ScoreGenerator(Tonality tonality) : chords(generateProgression(tonality)) {}
    SongScore generate();

private:
    static int calcNextMelodyNote(int chord, int note);

    static float calcNextMelodyVolume(float volume);

    SongScore score;
    std::vector<int> chords;
};
