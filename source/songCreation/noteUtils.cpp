#include <cmath>
#include "noteUtils.hpp"
#include "../utils.hpp"

int closestNote(int note, int source) {
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

int upperNoteTo(int t, int note) {
    while (note > t - 7) {
        note -= 7;
    }
    while (note < t) {
        note += 7;
    }
    return note;
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
