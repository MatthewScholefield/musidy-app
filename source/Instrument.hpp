#pragma once

#include <string>
#include <vector>
#include "tsf.h"
#include "utils.hpp"

/**
 * Scale tonality
 */
enum class Tonality : int {
    Major = 0,
    Minor = 1,
    MinorHarmonic = 2
};
constexpr int tonalityCount = 3;

/**
 *
 * @return Choose a random tonality probabilistically
 */
Tonality getRandomTonality();

/**
 * @param tonality Tonality enum
 * @return Capitalized string representing tonality
 */
std::string tonalityToString(Tonality tonality);

/**
 * Represents a virtual soundfont instrument oriented with
 * a scale that can be rendered into a float array
 */
class Instrument {
public:
    static constexpr int restNote = -1000;
    /**
     * Universal sound constants based on western music
     */
    static constexpr int notesPerOctave = 7, stepsPerOctave = 12;

    /**
     * Create a new instrument from a soundfont file
     * @param filename .sf2 file
     * @param gainDb Amount of volume change in decibels
     */
    explicit Instrument(const std::string &filename, float gainDb = 0);

    /**
     * Sets the scale
     * @param baseNote Root note of the scale
     * @param tonality The tonality of the scale
     */
    void setScale(int baseNote, Tonality tonality);

    /**
     * Produce a note in the virtual instrument
     * @param note Offset from the root note to play. 0 is base note
     * @param volume Loudness of note
     */
    void play(int note, float volume = 1.f);

    /**
     * Play a chromatic note
     * @param note chromatic note
     * @param volume Loudness of note
     */
    void playRaw(int note, float volume = 1.f);

    /**
     * Render notes into a flout array
     * @param data Float array to write samples to
     * @param n Number of samples to write
     */
    void render(float *data, size_t n);

    /**
     * @return Tonality of instrument
     */
    Tonality getTonality() const;

private:
    tsf *soundFont;  // Soundfont renderer
    int baseNote = 60;  // Note of scale
    Tonality tonality = Tonality::Major;  // Tonality of key

    static const int halfSteps[][notesPerOctave];  // Number of halfsteps in relation to root
};
