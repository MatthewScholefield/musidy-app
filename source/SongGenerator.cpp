#include <climits>
#include <iostream>
#include "SongGenerator.hpp"


const Color SongGenerator::chordColors[tonalityCount][Instrument::notesPerOctave] = {
        {  // Major
                {240, 240, 240},
                {130, 0, 0},
                {100, 200, 0},
                {200, 100, 100},
                {100, 100, 210},
                {50, 100, 240},
                {200, 200, 0}
        }, // Minor
        {
                {240, 240, 240},
                {130, 0, 0},
                {100, 200, 0},
                {200, 100, 100},
                {100, 100, 210},
                {50, 50, 180},
                {200, 200, 0}
        }, // Minor Harmonic
        {
                {240, 240, 240},
                {130, 0, 0},
                {100, 200, 0},
                {200, 100, 100},
                {100, 100, 210},
                {50, 50, 180},
                {200, 200, 0}
        }
};

SongGenerator::SongGenerator(Instrument &instrument, ParticleSystem &particles) :
        chords(generateProgression()), particles(particles) {
    instrument.setScale(60, getRandomTonality());
}

void SongGenerator::update(Instrument &instrument, double dt) {
    if ((noteTimer -= dt) < 0.0) {
        noteTimer = noteInterval;
        updateBeat(instrument);
    }
}

std::vector<int> SongGenerator::generateProgression() {
    std::vector<int> chords;
    chords.push_back(0);
    std::vector<int> chordFreq = {0, 0, 0, 0, 0, 0, 0};
    do {
        auto probs = getChordProbs(chords.back());

        for (int i = 0; i < probs.size(); ++i) {
            int freq = chordFreq[i] + 1;
            probs[i] /= freq * freq * freq;
        }

        int chord = selectSample(probs);
        if (chord != 0) {
            ++chordFreq[chord];
        }

        chords.push_back(closestNote(chord, chords.back()));
    } while ((chords.back() + 100 * 7) % 7 != 0 || chords.size() < 4);

    if (chords.size() % 2 == 1) {
        if (chords.size() >= 7) {
            chords.push_back(closestNote(0, chords.back()));
        } else {
            chords.pop_back();
        }
    }

    return chords;
}

int SongGenerator::closestNote(int note, int source) {
    int noteDist = std::abs(note - source);
    int otherDist = std::abs(note + 7 - source);
    int other2Dist = std::abs(note - 7 - source);
    int bestNote = note;
    if (otherDist < noteDist) {
        noteDist = otherDist;
        bestNote = note + 7;
    }
    if (other2Dist < noteDist) {
        bestNote = note - 7;
    }
    return bestNote;
}

const std::vector<int> SongGenerator::getProgression() {
    return chords;
}

void SongGenerator::setDelta(float dt) {
    noteInterval = dt;
}

static float randFloat() {
    return rand() / float(INT_MAX);
}

void SongGenerator::updateBeat(Instrument &instrument) {
    if (arpeggioNote == 0) {
        chordPos = int((chordPos + 1) % chords.size());
        createChordParticles(instrument.getTonality(), chords[chordPos]);
        instrument.playChord(chords[chordPos], 0.6f);
    }
    if ((chords[chordPos] + 7 * 100) % 7 != 0 || arpeggioNote == 0 || chordPos != chords.size() - 1) {
        instrument.play(chords[chordPos] + arpeggioNote, 0.6f);
    }
    arpeggioNote += arpeggioDelta;
    if (arpeggioNote == 0 || arpeggioNote >= 4) {
        arpeggioDelta *= -1;
    }
}

std::vector<float> SongGenerator::getChordProbs(int previous) {
    switch ((previous + 1 + 7 * 100) % 7) {
        case 0:
            return {0, 0.2f, 0.6f, 0.8f, 0.5f, 0.4f, 0};
        case 1:
            return {0, 0.3f, 1, 2, 2, 1, 0.5f};
        case 2:
            return {0, 0, 0, 0, 1, 0, 0, 0};
        case 3:
            return {0, 0, 0, 0.2f, 0, 1, 0};
        case 4:
            return {3, 0, 0, 0, 2, 1.5f, 0.1f};
        case 5:
            return {1.5f, 0, 0.2f, 0.5f, 0, 0.5f, 0.1f};
        case 6:
            return {0, 0, 0.3f, 1, 0.2f, 0, 0};
        case 7:
            return {1, 0, 0, 0, 0, 0, 0};
        default:
            throw std::invalid_argument("Invalid chord: " + std::to_string(previous));
    }
}

void SongGenerator::createChordParticles(Tonality tonality, int chord) {
    for (int i = 0; i < particlesPerChord; ++i) {
        particles.add(Particle(
                -1.f + 3.f * randFloat(),
                -1.f + 3.f * randFloat(),
                0.6f * randFloat() - 0.3f,
                0.6f * randFloat() - 0.3f,
                chordColors[int(tonality)][chord],
                noteInterval * 4 * 1.2f
        ));
    }
}
