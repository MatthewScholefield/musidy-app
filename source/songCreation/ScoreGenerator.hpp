#pragma once

#include "ScorePlayer.hpp"
#include "MusicScore.hpp"
#include "../Instrument.hpp"
#include "chordProgressions.hpp"
#include "noteUtils.hpp"

/**
 * A class to build music scores
 */
class ScoreGenerator {
public:
    /**
     * Create a new music score generator from a tonality
     * @param tonality Tonality of song to generate
     */
    explicit ScoreGenerator(Tonality tonality) : chords(generateProgression(tonality)) {}

    /**
     * Create a new music score generator from chords
     * @param chords Array of chord notes
     */
    explicit ScoreGenerator(std::vector<int> chords) : chords(std::move(chords)) {}

    /**
     * Generate the notes in the whole song
     * @return Music score of song
     */
    MusicScore generate();

private:
    /**
     * Find the next note in the melody given the previous note and current chord
     * @param chord Current chord
     * @param note Previous note
     * @return Next note of melody
     */
    static int calcNextMelodyNote(int chord, int note);

    /**
     * Find the next melody note volume given the previous volume
     * @param volume Previous volume
     * @return Next volume of note
     */
    static float calcNextMelodyVolume(float volume);

    MusicScore score;
    std::vector<int> chords;
};
