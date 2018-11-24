#pragma once

#include <string>
#include "tsf.h"

class Instrument {
public:
  explicit Instrument(const std::string &filename, float gain_db = 0);
  void render(float *data, size_t n);
  void play(int note, float volume = 1.f);

private:
  tsf* tsf_;
};
