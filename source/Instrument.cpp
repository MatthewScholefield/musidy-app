#include <iostream>
#include <cmath>
#include "Instrument.hpp"
#include "SoundSystem.hpp"

constexpr int Instrument::kHalfsteps[][Instrument::kNotesPerOctave] = {
    {0, 2, 4, 5, 7, 9, 11},
    {0, 2, 3, 5, 7, 8, 10},
    {0, 2, 3, 5, 7, 8, 11}
};

Instrument::Instrument(const std::string &filename, float gain_db) :
    tsf_(tsf_load_filename(filename.c_str())) {
  tsf_set_output(tsf_, TSF_STEREO_INTERLEAVED, SoundSystem::kSampleRate, gain_db);
}

void Instrument::Play(int note, float volume) {
  int num_octaves = int(std::floor(note / float(kNotesPerOctave)));
  int scale_degree = note - num_octaves * kNotesPerOctave;
  int chromatic = kStepsPerOctave * num_octaves + kHalfsteps[int(tonality_)][scale_degree];
  chromatic += base_note_;
  if (chromatic < 0) {
    throw std::runtime_error("Invalid note: " + std::to_string(note));
  }
  PlayRaw(chromatic, volume);
}

void Instrument::PlayRaw(int note, float volume) {
  tsf_note_on(tsf_, 0, note, volume);
}

void Instrument::Render(float *data, size_t n) {
  tsf_render_float(tsf_, data, int(n), 0);
}

void Instrument::SetScale(int base_note, Tonality tonality) {
  base_note_ = base_note;
  tonality_= tonality;
}

void Instrument::PlayChord(int base, float volume) {
  Play(base, volume);
  Play(base + 2, volume);
  Play(base + 4, volume);
}
