#pragma once

#include <vector>
#include <stdexcept>
#include "Instrument.hpp"
#include "ParticleSystem.hpp"

class SongGenerator {
public:
  explicit SongGenerator(Instrument &instrument, ParticleSystem &particles);
  void update(Instrument &instrument, double dt);

  const std::vector<int> getProgression() {
    return chords;
  }
  static int closestNote(int note, int source);

  void setDelta(float dt) {
    noteInterval = dt;
  }

private:
  void updateBeat(Instrument &instrument);
  std::vector<int> generateProgression();
  static std::vector<float> getChordProbs(int previous);

  double noteInterval = 0.4;

  double noteTimer = 0.0;
  int chordPos = -1;
  int arpeggioNote = 0;
  int arpeggioDelta = 2;
  std::vector<int> chords;
  ParticleSystem &particles;
};
