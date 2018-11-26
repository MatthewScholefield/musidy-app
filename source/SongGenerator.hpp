#pragma once

#include "Instrument.hpp"

class SongGenerator {
public:
  explicit SongGenerator(Instrument &instrument);
  void Update(Instrument &instrument, double dt);

private:
  void UpdateBeat(Instrument &instrument);

  static constexpr double kNoteInterval = 0.2;

  double note_timer_ = 0.0;
  int chord_pos_ = -1;
  int arpeggio_note_ = 0;
  int arpeggio_delta_ = 2;
  static const int kChords[];
};
