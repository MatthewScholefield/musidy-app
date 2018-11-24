#pragma once

#include <string>
#include "tsf.h"

enum class Tonality : int {
  kMajor = 0,
  kMinor = 1,
  kMinorHarmonic = 2
};


class Instrument {
public:
  static constexpr int kNotesPerOctave = 7, kStepsPerOctave = 12;
  explicit Instrument(const std::string &filename, float gain_db = 0);

  void SetScale(int base_note, Tonality tonality);
  void Play(int note, float volume = 1.f);
  void PlayChord(int base, float volume = 1.f);
  void PlayRaw(int note, float volume = 1.f);
  void Render(float *data, size_t n);

private:
  tsf *tsf_;
  int base_note_ = 60;
  Tonality tonality_ = Tonality::kMajor;

  static const int kHalfsteps[][kNotesPerOctave];
};
