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

int upperNoteTo(int note, int degree) {
    while (degree > note + 7) {
        degree -= 7;
    }
    while (degree <= note) {
        degree += 7;
    }
    return degree;
}

int lowerNoteTo(int note, int degree) {
    while (degree < note - 7) {
        degree += 7;
    }
    while (degree >= note) {
        degree -= 7;
    }
    return degree;
}

int getDegree(int note) {
    return (note + 100 * 7) % 7;
}
