#include <climits>
#include <iostream>
#include "SongGenerator.hpp"


SongGenerator::SongGenerator(Instrument &instrument) : chords_(GenerateProgression()) {
  instrument.SetScale(60, GetRandomTonality());
}

void SongGenerator::Update(Instrument &instrument, double dt) {
  if ((note_timer_ -= dt) < 0.0) {
    note_timer_ = note_interval_;
    UpdateBeat(instrument);
  }
}

void SongGenerator::UpdateBeat(Instrument &instrument) {
  if (arpeggio_note_ == 0) {
    chord_pos_ = int((chord_pos_ + 1) % chords_.size());
    instrument.PlayChord(chords_[chord_pos_], 0.6f);
  }
  if ((chords_[chord_pos_] + 7 * 100) % 7 != 0 || arpeggio_note_ == 0 || chord_pos_ != chords_.size() - 1) {
    instrument.Play(chords_[chord_pos_] + arpeggio_note_, 0.6f);
  }
  arpeggio_note_ += arpeggio_delta_;
  if (arpeggio_note_ == 0 || arpeggio_note_ >= 4) {
    arpeggio_delta_ *= -1;
  }
}

std::vector<int> SongGenerator::GenerateProgression() {
  std::vector<int> chords;
  chords.push_back(0);
  std::vector<int> chordFreq = {0, 0, 0, 0, 0, 0, 0};
  do {
    auto probs = GetChordProbs(chords.back());

    for (int i = 0; i < probs.size(); ++i) {
      int freq = chordFreq[i] + 1;
      probs[i] /= freq * freq * freq;
    }

    int chord = SelectSample(probs);
    if (chord != 0) {
      ++chordFreq[chord];
    }

    chords.push_back(ClosestNote(chord, chords.back()));
  } while ((chords.back() + 100 * 7) % 7 != 0 || chords.size() < 4);

  if (chords.size() % 2 == 1) {
    if (chords.size() >= 7) {
      chords.push_back(ClosestNote(0, chords.back()));
    } else {
      chords.pop_back();
    }
  }

  return chords;
}

std::vector<float> SongGenerator::GetChordProbs(int previous) {
  switch ((previous + 1 + 7 * 100) % 7) {
    case 0:
      return {0, 0.2f, 0.6f, 0.8f, 0.5f, 0.4f, 0};
    case 1:
      return {0, 0.3f, 1, 2, 2, 1, 0.5f};
    case 2:
      return {0, 0, 0, 0, 1, 0, 0, 0};
    case 3:
      return {0, 0, 0, 0.2f, 0, 1, 0};
    case 4:
      return {3, 0, 0, 0, 2, 1.5f, 0.1f};
    case 5:
      return {1.5f, 0, 0.2f, 0.5f, 0, 0.5f, 0.1f};
    case 6:
      return {0, 0, 0.3f, 1, 0.2f, 0, 0};
    case 7:
      return {1, 0, 0, 0, 0, 0, 0};
    default:
      throw std::invalid_argument("Invalid chord: " + std::to_string(previous));
  }
}

int SongGenerator::ClosestNote(int note, int source) {
  int noteDist = std::abs(note - source);
  int otherDist = std::abs(note + 7 - source);
  int other2Dist = std::abs(note -  7 - source);
  int bestNote = note;
  if (otherDist < noteDist) {
    noteDist = otherDist;
    bestNote = note + 7;
  }
  if (other2Dist < noteDist) {
    bestNote = note - 7;
  }
  return bestNote;
}
