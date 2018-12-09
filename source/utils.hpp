#pragma once

#include <vector>
#include <climits>
#include <cstdlib>
#include <stdexcept>

/**
 * Choose a random index based on the given probabilities
 * @param probs Vector of float probabilities
 * @return Index of randomly chosen element
 */
int selectSample(const std::vector<float> &probs);
