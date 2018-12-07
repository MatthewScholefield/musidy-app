#pragma once

#include <vector>
#include <stdexcept>
#include "Instrument.hpp"
#include "ParticleSystem.hpp"

class SongGenerator {
public:
  explicit SongGenerator(Instrument &instrument, ParticleSystem &particles);
  void Update(Instrument &instrument, double dt);

  const std::vector<int> GetProgression() {
    return chords_;
  }
  static int ClosestNote(int note, int source);

  void SetDelta(float dt) {
    note_interval_ = dt;
  }

private:
  void UpdateBeat(Instrument &instrument);
  std::vector<int> GenerateProgression();
  static std::vector<float> GetChordProbs(int previous);

  double note_interval_ = 0.4;

  double note_timer_ = 0.0;
  int chord_pos_ = -1;
  int arpeggio_note_ = 0;
  int arpeggio_delta_ = 2;
  std::vector<int> chords_;
  ParticleSystem &particles_;
};
