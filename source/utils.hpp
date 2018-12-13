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

/**
 * @return A random float between 0.0 and 1.0
 */
float randFloat();

template<typename T>
T min(T a) {
    return a;
}

template<typename T>
T min(T a, T b) {
    return a < b ? a : b;
}

/**
 * Return the minimum value of a sequence
 * @param a First value
 * @param b Second value
 * @param args Other values
 * @return Minimum of all values
 */
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

/**
 * Return the value with the minimum distance to a target
 * @param t Target value
 * @param a First value
 * @param b Second value
 * @param args Other values
 * @return Value closest to the target
 */
template<typename T, typename...Args>
T minTo(T t, T a, T b, Args...args) {
    return minTo(t, minTo(t, a, b), args...);
}
