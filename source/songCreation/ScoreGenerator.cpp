#include "ScoreGenerator.hpp"
#include "../utils.hpp"

MusicScore ScoreGenerator::generate() {
    for (int measureNum = 0; measureNum < numMeasures; ++measureNum) {
        for (int chordPos = 0; chordPos < chords.size(); ++chordPos) {
            generateBassMeasure(chordPos);
            generateMelodyMeasure(chordPos);
            generateHarmonyMeasure(chordPos);
        }
    }
    return score;
}

int ScoreGenerator::calcNextMelodyNote(int chord, int note) {
    int lower = minTo(note, lowerNoteTo(note, chord), lowerNoteTo(note, chord + 2), lowerNoteTo(note, chord + 4));
    int upper = minTo(note, upperNoteTo(note, chord), upperNoteTo(note, chord + 2), upperNoteTo(note, chord + 4));

    const int melodyRange = 12, melodyMin = 8;
    float pos = std::min(1.f, std::max(0.f, (note - chord - melodyMin) / float(melodyRange)));

    std::vector<int> options = {lower, upper};
    std::vector<float> probs = {pos, 1.f - pos};

    if (getDegree(note) == getDegree(chord) ||
        getDegree(note) == getDegree(chord + 2) ||
        getDegree(note) == getDegree(chord + 4)) {
        options.push_back(note);
        probs.push_back(0.1f);
    }

    return options[selectSample(probs)];
}

float ScoreGenerator::calcNextMelodyVolume(float volume) {
    const float melMin = 0.3f, melMax = 0.8f;
    float volPos = std::max(0.f, std::min(1.f, (volume - melMin) / (melMax - melMin)));
    int voldir = selectSample({sqrt(volPos), 0.1f, sqrt(1.f - volPos)}) - 1;
    return volume + voldir * 0.1f * randFloat();
}

void ScoreGenerator::generateMelodyMeasure(int chordPos) {
    for (int noteNum = 0; noteNum < 4; ++noteNum) {
        if (rand() % 5 != 0 || slideInProgress) {
            if (!slideInProgress && noteNum == 0 && rand() % 5 == 0) {
                slideInProgress = true;
            } else {
                slideInProgress = false;
                melodyNote = calcNextMelodyNote(chords[chordPos], melodyNote);
            }
            melodyVolume = calcNextMelodyVolume(melodyVolume);
            score.add(SongPart::Melody, melodyNote, melodyVolume);
        } else {
            score.add(SongPart::Melody);
        }
    }
}

void ScoreGenerator::generateHarmonyMeasure(int chordPos) {
    int root = chords[chordPos];
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

void ScoreGenerator::generateBassMeasure(int chordPos) {
    int root = chords[chordPos];
    score.add(SongPart::Bass, root - 7, 0.6f);
    score.add(SongPart::Chords, {root, root + 2, root + 4}, 0.6f);
}
