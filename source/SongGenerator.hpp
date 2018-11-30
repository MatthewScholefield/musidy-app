#pragma once

#include <vector>
#include <stdexcept>
#include "Instrument.hpp"

class SongGenerator {
public:
  explicit SongGenerator(Instrument &instrument);
  void Update(Instrument &instrument, double dt);

  const std::vector<int> GetProgression() {
    return chords_;
  }

private:
  void UpdateBeat(Instrument &instrument);

  std::vector<int> GetChordSequence();

  static std::vector<float> GetChordProbs(int previous);

  static constexpr double kNoteInterval = 0.4;

  double note_timer_ = 0.0;
  int chord_pos_ = -1;
  int arpeggio_note_ = 0;
  int arpeggio_delta_ = 2;
  std::vector<int> chords_;
};
