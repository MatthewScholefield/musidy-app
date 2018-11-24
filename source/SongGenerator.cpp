#include "SongGenerator.hpp"

SongGenerator::SongGenerator(Instrument &instrument) {
  instrument.SetScale(60, Tonality::kMinor);
}

void SongGenerator::Update(Instrument &instrument, double dt) {
  if ((note_timer_ -= dt) < 0.0) {
    note_timer_ = kNoteInterval;
    UpdateBeat(instrument);
  }
}

void SongGenerator::UpdateBeat(Instrument &instrument) {
  instrument.Play(note_);
  note_ += moving_up_ ? 1 : -1;
  if (note_ >= Instrument::kNotesPerOctave || note_ <= 0) {
    moving_up_ = !moving_up_;
  }
}
