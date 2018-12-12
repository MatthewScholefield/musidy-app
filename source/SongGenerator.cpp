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
                {50, 50,  180},
                {200, 200, 0}
        }, // Minor Harmonic
        {
                {240, 240, 240},
                {130, 0, 0},
                {100, 200, 0},
                {200, 100, 100},
                {100, 100, 210},
                {50, 50,  180},
                {200, 200, 0}
        }
};

SongGenerator::SongGenerator(Instrument &instrument, ParticleSystem &particles) :
        tonality(getRandomTonality()), chords(generateProgression()), particles(particles) {
    instrument.setScale(60, tonality);
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
        if (tonality == Tonality::MinorHarmonic) {
            probs[2] *= 0.001f;
        }

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

void SongGenerator::setNoteInterval(float noteInterval) {
    this->noteInterval = noteInterval;
}

static float randFloat() {
    return rand() / float(RAND_MAX);
}

template<typename T, typename...Args>
T min(T a, T b, Args...args) {
    return min(min(a, b), args...);
}

template<typename T>
T min(T a, T b) {
    return a < b ? a : b;
}

template<typename T>
T minTo(T t, T a, T b) {
    return abs(t - a) < abs(t - b) ? a : b;
}

template<typename T>
T minTo(T t, T a) {
    return a;
}

template<typename T, typename...Args>
T minTo(T t, T a, T b, Args...args) {
    return minTo(t, minTo(t, a, b), args...);
}



int lowerNoteTo(int t, int note) {
    while (note < t - 7) {
        note += 7;
    }
    while (note > t) {
        note -= 7;
    }
    return note;
}

void SongGenerator::updateBeat(Instrument &instrument) {
    if (arpeggioNote == 0) {
        chordPos = int((chordPos + 1) % chords.size());
        createChordParticles(instrument.getTonality(), chords[chordPos]);
        instrument.playChord(chords[chordPos], 0.6f);
    }

    if (rand() % 5 != 0 || slideInProgress) {
        if (!slideInProgress && arpeggioNote == 0 && rand() % 5 == 0) {
            slideInProgress = true;
        } else {
            slideInProgress = false;
            melodyNote = calcNextMelodyNote(chords[chordPos], melodyNote);
        }
        melodyVolume = calcNextMelodyVolume(melodyVolume);
        createNoteParticles(instrument.getTonality(), melodyNote);
        instrument.play(melodyNote, melodyVolume);
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
                chordColors[int(tonality)][(chord + Instrument::notesPerOctave * 100) % Instrument::notesPerOctave],
                noteInterval * 4 * 1.5f
        ));
    }
}

void SongGenerator::createNoteParticles(Tonality tonality, int note) {
    float partX = randFloat();
    float partY = randFloat();
    for (int i = 0; i < particlesPerChord; ++i) {
        particles.add(Particle(
                partX + 0.3f * randFloat() - 0.15f,
                partY + 0.3f * randFloat() - 0.15f,
                0.4f * randFloat() - 0.2f,
                0.4f * randFloat() - 0.2f,
                chordColors[int(tonality)][(note + Instrument::notesPerOctave * 100) % Instrument::notesPerOctave],
                noteInterval * 4 * 1.5f
        ));
    }
}

int SongGenerator::calcNextMelodyNote(int chord, int note) {
    chord += 7;
    int a = lowerNoteTo(note, chord);
    int b = lowerNoteTo(note, chord + 2);
    int c = lowerNoteTo(note, chord + 4);
    int lowerOption = minTo(note, a, b, c);
    int upperOption = minTo(note, a + 7, b + 7, c + 7);
    int options[] = {lowerOption, upperOption};
    const int melodyRange = 12, melodyMin = 0;
    float pos = std::min(1.f, std::max(0.f, (note - chord - melodyMin) / float(melodyRange)));
    return options[selectSample({sqrt(pos), sqrt(1.f - pos)})];
}

float SongGenerator::calcNextMelodyVolume(float volume) {
    const float melMin = 0.3f, melMax = 0.8f;
    float volPos = std::max(0.f, std::min(1.f, (volume - melMin) / (melMax - melMin)));
    int voldir = selectSample({sqrt(volPos), 0.1f, sqrt(1.f - volPos)}) - 1;
    return volume + voldir * 0.1f * randFloat();
}
