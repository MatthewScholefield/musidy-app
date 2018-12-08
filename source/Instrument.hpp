#pragma once

#include <string>
#include <vector>
#include "tsf.h"
#include "utils.hpp"

enum class Tonality : int {
    Major = 0,
    Minor = 1,
    MinorHarmonic = 2
};
constexpr int tonalityCount = 3;

Tonality getRandomTonality();
std::string tonalityToString(Tonality tonality);


class Instrument {
public:
    static constexpr int notesPerOctave = 7, stepsPerOctave = 12;
    explicit Instrument(const std::string &filename, float gainDb = 0);

    void setScale(int baseNote, Tonality tonality);
    void play(int note, float volume = 1.f);
    void playChord(int base, float volume = 1.f);
    void playRaw(int note, float volume = 1.f);
    void render(float *data, size_t n);
    Tonality getTonality() const;

private:
    tsf *soundFont;
    int baseNote = 60;
    Tonality tonality = Tonality::Major;

    static const int halfSteps[][notesPerOctave];
};
