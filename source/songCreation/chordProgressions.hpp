#pragma once
#include <vector>
#include "../Instrument.hpp"

/**
 * Get the probability distribution for the
 * next chord given the previous chord
 * @param previous Previous chord degree
 * @return Next chord probability distribution
 */
std::vector<float> getChordProbs(int previous);

/**
 * Generate a nice sounding chord progression using
 * probabilities and discouraging repeated chords
 * @return Chord degree integers as vector. May also be higher octaves
 */
std::vector<int> generateProgression(Tonality tonality);
