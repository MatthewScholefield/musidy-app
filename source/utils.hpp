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
float randFloat();

template<typename T>
T min(T a) {
    return a;
}

template<typename T>
T min(T a, T b) {
    return a < b ? a : b;
}

template<typename T, typename...Args>
T min(T a, T b, Args...args) {
    return min(min(a, b), args...);
}

template<typename T>
T minTo(T t, T a) {
    return a;
}

template<typename T>
T minTo(T t, T a, T b) {
    return abs(t - a) < abs(t - b) ? a : b;
}

template<typename T, typename...Args>
T minTo(T t, T a, T b, Args...args) {
    return minTo(t, minTo(t, a, b), args...);
}
