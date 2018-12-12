#include <stdexcept>
#include "chordProgressions.hpp"
#include "../Instrument.hpp"
#include "noteUtils.hpp"

std::vector<float> getChordProbs(int previous) {
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

std::vector<int> generateProgression(Tonality tonality) {
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
