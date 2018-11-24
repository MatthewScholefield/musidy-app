#pragma once

#include "Instrument.hpp"

class SongGenerator {
public:
  explicit SongGenerator(Instrument &instrument);
  void Update(Instrument &instrument, double dt);

private:
  void UpdateBeat(Instrument &instrument);

  static constexpr double kNoteInterval = 1.0;

  double note_timer_ = 0.0;
  int chord_pos_ = 0;
  static const int kChords[];
};
