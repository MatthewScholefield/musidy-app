#pragma once

#include "Instrument.hpp"

class SongGenerator {
public:
  explicit SongGenerator(Instrument &instrument);
  void Update(Instrument &instrument, double dt);

private:
  void UpdateBeat(Instrument &instrument);

  static constexpr double kNoteInterval = 0.2;

  int note_ = 0;
  double note_timer_ = 0.0;
  bool moving_up_ = true;
};
