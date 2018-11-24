#pragma once

#include "Instrument.hpp"

class SongGenerator {
public:
  void Update(Instrument &instrument, double dt);

private:
  static constexpr double kNoteInterval = 0.2;

  int note_ = 60;
  double note_timer_ = 0.0;
  bool moving_up_ = true;
};
