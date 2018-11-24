#include "SongGenerator.hpp"

void SongGenerator::Update(Instrument &instrument, double dt) {
  if ((note_timer_ -= dt) < 0.0) {
    note_timer_ = kNoteInterval;
    instrument.Play(note_);
    note_ += moving_up_ ? 1 : -1;
    if (note_ >= 60 + 12 || note_ <= 60) {
      moving_up_ = !moving_up_;
    }
  }
}
