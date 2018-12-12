#pragma once

#include <vector>
#include <stdexcept>
#include "../Instrument.hpp"
#include "../ParticleSystem.hpp"
#include "SongScore.hpp"

/**
 * Plays a dynamically generated song on the given instrument
 */
class ScorePlayer {
public:
    /**
     * Create a new song generator
     * @param instrument The instrument to initialize
     * @param particles The particles system to visualize to
     */
    explicit ScorePlayer(Instrument &instrument, ParticleSystem &particles);

    /**
     * Update the song with the given delta time
     * @param instrument The instrument to play on
     * @param dt Amount of time of the song to play
     */
    void update(Instrument &instrument, double dt);

    /**
     * @return The chord progression that's being played
     */
    const std::vector<int> getProgression();

    /**
     * Set the delay time between beats
     * @param noteInterval Time to set as separation between notes
     */
    void setNoteInterval(float noteInterval);

private:
    const float particlesPerChord = 400; // Number of particles to create per chord
    const float particlesPerNote = 40; // Number of particles to create per chord

    /**
     * Create the particles for a chord in the given tonality
     * @param tonality Tonality of  key
     * @param chord Chord root degree
     */
    void createChordParticles(Tonality tonality, int chord);

    /**
     * Create the particles for a note in the given tonality
     * @param tonality Tonality of  key
     * @param note Note being visualizeds
     */
    void createNoteParticles(Tonality tonality, int note);

    // Colors for chords by tonality
    static const Color chordColors[tonalityCount][Instrument::notesPerOctave];
    double noteInterval = 0.4;
    double noteTimer = 0.0;

    SongScore score;

    Tonality tonality;
    std::vector<int> chords;
    ParticleSystem &particles;
};
