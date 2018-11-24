#include "Instrument.hpp"
#include "SoundSystem.hpp"

Instrument::Instrument(const std::string &filename, float gain_db) :
    tsf_(tsf_load_filename(filename.c_str())) {
  tsf_set_output(tsf_, TSF_STEREO_INTERLEAVED, SoundSystem::kSampleRate, gain_db);
}

void Instrument::Play(int note, float volume) {
  tsf_note_on(tsf_, 0, note, volume);
}

void Instrument::Render(float *data, size_t n) {
  tsf_render_float(tsf_, data, int(n), 0);
}
