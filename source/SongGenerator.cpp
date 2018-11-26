#include "SongGenerator.hpp"


const int SongGenerator::kChords[] = {1, 6 - 7, 3, 0};

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
  if (arpeggio_note_ == 0) {
    chord_pos_ = (chord_pos_ + 1) % 4;
    instrument.PlayChord(kChords[chord_pos_] - 1, 0.6f);
  }
  instrument.Play(kChords[chord_pos_] - 1 + arpeggio_note_, 0.6f);
  arpeggio_note_ += arpeggio_delta_;
  if (arpeggio_note_ == 0 || arpeggio_note_ >= 4) {
    arpeggio_delta_ *= -1;
  }
}
