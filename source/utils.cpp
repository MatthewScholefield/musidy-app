#include "utils.hpp"


int selectSample(const std::vector<float> &probs) {
    float sum = 0.f;
    for (auto i : probs) {
        sum += i;
    }
    float choice = sum * (rand() / float(RAND_MAX));
    for (int i = 0; i < probs.size(); ++i) {
        choice -= probs[i];
        if (choice <= 0) {
            return i;
        }
    }
    throw std::runtime_error("Statistical anomaly: " + std::to_string(choice));
}

float randFloat() {
    return rand() / float(RAND_MAX);
}
