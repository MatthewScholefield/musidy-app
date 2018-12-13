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
     * Generate a measure of the melody line
     * @param chord Index of chord array
     */
    void generateMelodyMeasure(int chordPos);

    /**
     * Generate a measure of the harmony line
     * @param chordPos Index of chord array
     */
    void generateHarmonyMeasure(int chordPos);

    /**
     * Generate a measure of the bass line
     * @param chordPos Index of the chord array
     */
    void generateBassMeasure(int chordPos);

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
    int numMeasures = 2;
    int melodyNote = 0;
    bool slideInProgress = false;
    float melodyVolume = 0.5f;
};
