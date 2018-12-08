#pragma once

#include <vector>
#include <stdexcept>
#include "Instrument.hpp"
#include "ParticleSystem.hpp"

class SongGenerator {
public:
    explicit SongGenerator(Instrument &instrument, ParticleSystem &particles);
    void update(Instrument &instrument, double dt);

    static int closestNote(int note, int source);
    const std::vector<int> getProgression();
    void setDelta(float dt);

private:
    const float particlesPerChord = 400;
    void updateBeat(Instrument &instrument);
    std::vector<int> generateProgression();
    static std::vector<float> getChordProbs(int previous);
    void createChordParticles(Tonality tonality, int chord);

    // Colors for chords by tonality
    static const Color chordColors[tonalityCount][Instrument::notesPerOctave];
    double noteInterval = 0.4;
    double noteTimer = 0.0;
    int chordPos = -1;
    int arpeggioNote = 0;
    int arpeggioDelta = 2;
    std::vector<int> chords;
    ParticleSystem &particles;
};
