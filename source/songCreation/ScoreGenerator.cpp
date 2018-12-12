#include "ScoreGenerator.hpp"
#include "../utils.hpp"

SongScore ScoreGenerator::generate() {
    int numMeasures = 2;
    int melodyNote = 0;
    float melodyVolume = 0.5f;
    for (int measureNum = 0; measureNum < numMeasures; ++measureNum) {
        bool slideInProgress = false;
        for (int chordPos = 0; chordPos < chords.size(); ++chordPos) {
            int root = chords[chordPos];
            score.add(SongPart::Chords, {root - 7, root, root + 2, root + 4}, 0.6f);
            for (int noteNum = 0; noteNum < 4; ++noteNum) {
                if (rand() % 5 != 0 || slideInProgress) {
                    if (!slideInProgress && noteNum == 0 && rand() % 5 == 0) {
                        slideInProgress = true;
                    } else {
                        slideInProgress = false;
                        melodyNote = calcNextMelodyNote(root, melodyNote);
                    }
                    melodyVolume = calcNextMelodyVolume(melodyVolume);
                    score.add(SongPart::Melody, melodyNote, melodyVolume);
                } else {
                    score.add(SongPart::Melody);
                }
            }
            if (chordPos != chords.size() - 1 || (root + 7 * 100) % 7 != 0) {
                score.add(SongPart::Harmony, root + 0, 0.6f);
                score.add(SongPart::Harmony, root + 2, 0.6f);
                score.add(SongPart::Harmony, root + 4, 0.6f);
                score.add(SongPart::Harmony, root + 2, 0.6f);
            } else {
                score.add(SongPart::Harmony, root + 0, 0.6f);
                score.add(SongPart::Harmony);
                score.add(SongPart::Harmony);
                score.add(SongPart::Harmony);
            }
        }
    }
    return score;
}

int ScoreGenerator::calcNextMelodyNote(int chord, int note) {
    chord += 7;
    int a = lowerNoteTo(note, chord);
    int b = lowerNoteTo(note, chord + 2);
    int c = lowerNoteTo(note, chord + 4);
    int lowerOption = minTo(note, a, b, c);
    int upperOption = minTo(note, a + 7, b + 7, c + 7);
    int options[] = {lowerOption, upperOption};
    const int melodyRange = 12, melodyMin = 0;
    float pos = std::min(1.f, std::max(0.f, (note - chord - melodyMin) / float(melodyRange)));
    return options[selectSample({sqrt(pos), sqrt(1.f - pos)})];
}

float ScoreGenerator::calcNextMelodyVolume(float volume) {
    const float melMin = 0.3f, melMax = 0.8f;
    float volPos = std::max(0.f, std::min(1.f, (volume - melMin) / (melMax - melMin)));
    int voldir = selectSample({sqrt(volPos), 0.1f, sqrt(1.f - volPos)}) - 1;
    return volume + voldir * 0.1f * randFloat();
}
