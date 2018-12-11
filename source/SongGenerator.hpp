#pragma once

#include <vector>
#include <stdexcept>
#include "Instrument.hpp"
#include "ParticleSystem.hpp"

/**
 * Plays a dynamically generated song on the given instrument
 */
class SongGenerator {
public:
    /**
     * Create a new song generator
     * @param instrument The instrument to initialize
     * @param particles The particles system to visualize to
     */
    explicit SongGenerator(Instrument &instrument, ParticleSystem &particles);

    /**
     * Update the song with the given delta time
     * @param instrument The instrument to play on
     * @param dt Amount of time of the song to play
     */
    void update(Instrument &instrument, double dt);

    /**
     * Find the note closest to another note, ignoring octaves
     * @param note Scale degree (without octave)
     * @param source Note to map to
     * @return Scale degree offset by some octaves
     */
    static int closestNote(int note, int source);

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

    /**
     * Called ever beat of the song
     * @param instrument Instrument to play to
     */
    void updateBeat(Instrument &instrument);

    /**
     * Generate a nice sounding chord progression using
     * probabilities and discouraging repeated chords
     * @return Chord degree integers as vector. May also be higher octaves
     */
    std::vector<int> generateProgression();

    /**
     * Get the probability distribution for the
     * next chord given the previous chord
     * @param previous Previous chord degree
     * @return Next chord probability distribution
     */
    static std::vector<float> getChordProbs(int previous);

    /**
     * Create the particles for a chord in the given tonality
     * @param tonality Tonality of  key
     * @param chord Chord root degree
     */
    void createChordParticles(Tonality tonality, int chord);

    // Colors for chords by tonality
    static const Color chordColors[tonalityCount][Instrument::notesPerOctave];
    double noteInterval = 0.4;
    double noteTimer = 0.0;
    int chordPos = -1;
    int arpeggioNote = 0;
    int arpeggioDelta = 2;
    Tonality tonality;
    std::vector<int> chords;
    ParticleSystem &particles;
};
