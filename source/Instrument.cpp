#include <iostream>
#include <cmath>
#include "Instrument.hpp"
#include "SoundSystem.hpp"

constexpr int Instrument::halfSteps[][Instrument::notesPerOctave] = {
        {0, 2, 4, 5, 7, 9, 11},
        {0, 2, 3, 5, 7, 8, 10},
        {0, 2, 3, 5, 7, 8, 11}
};

Instrument::Instrument(const std::string &filename, float gainDb) :
        soundFont(tsf_load_filename(filename.c_str())) {
    tsf_set_output(soundFont, TSF_STEREO_INTERLEAVED, SoundSystem::sampleRate, gainDb);
}

void Instrument::play(int note, float volume) {
    if (note == restNote) {
        return;
    }
    int numOctaves = int(std::floor(note / float(notesPerOctave)));
    int scaleDegree = note - numOctaves * notesPerOctave;
    int chromatic = stepsPerOctave * numOctaves + halfSteps[int(tonality)][scaleDegree];
    chromatic += baseNote;
    if (chromatic < 0) {
        throw std::runtime_error("Invalid note: " + std::to_string(note));
    }
    playRaw(chromatic, volume);
}

void Instrument::playRaw(int note, float volume) {
    tsf_note_on(soundFont, 0, note, std::max(0.f, std::min(1.f, volume * volumeMultiplier)));
}

void Instrument::render(float *data, size_t n) {
    tsf_render_float(soundFont, data, int(n), 0);
}

void Instrument::setScale(int baseNote, Tonality tonality) {
    this->baseNote = baseNote;
    this->tonality = tonality;
}

Tonality Instrument::getTonality() const {
    return tonality;
}

void Instrument::setVolumeMultiplier(float volumeMultiplier) {
    this->volumeMultiplier = volumeMultiplier;
}

Tonality getRandomTonality() {
    return Tonality(selectSample({0.3f, 0.3f, 0.1f}));
}

std::string tonalityToString(Tonality tonality) {
    switch (tonality) {
        case Tonality::Major:
            return "Major";
        case Tonality::Minor:
            return "Minor";
        case Tonality::MinorHarmonic:
            return "Harmonic";
        default:
            throw std::invalid_argument("Invalid tonality: " + std::to_string(int(tonality)));
    }
}
