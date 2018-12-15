#include <climits>
#include <iostream>
#include "ScorePlayer.hpp"
#include "noteUtils.hpp"
#include "ScoreGenerator.hpp"
#include "../utils.hpp"


const Color ScorePlayer::chordColors[tonalityCount][Instrument::notesPerOctave] = {
        {  // Major
                {240, 240, 240},
                {130, 0, 0},
                {100, 200, 0},
                {200, 100, 100},
                {100, 100, 210},
                {50, 100, 240},
                {200, 200, 0}
        }, // Minor
        {
                {240, 240, 240},
                {130, 0, 0},
                {100, 200, 0},
                {200, 100, 100},
                {100, 100, 210},
                {50, 50,  180},
                {200, 200, 0}
        }, // Minor Harmonic
        {
                {240, 240, 240},
                {130, 0, 0},
                {100, 200, 0},
                {200, 100, 100},
                {100, 100, 210},
                {50, 50,  180},
                {200, 200, 0}
        }
};

ScorePlayer::ScorePlayer(Instrument &instrument, ParticleSystem &particles) :
        tonality(getRandomTonality()), chords(generateProgression(tonality)), particles(particles),
        score(ScoreGenerator(chords).generate()) {
    instrument.setScale(60, tonality);
}

void ScorePlayer::update(Instrument &instrument, double dt) {
    if ((noteTimer -= dt) < 0.0) {
        noteTimer = noteInterval;
        const auto &chordNotes = score.getCurrentNotes(SongPart::Chords);
        if (!chordNotes.empty()) {
            createChordParticles(tonality, chordNotes[0].note);
        }
        const auto &melodyNotes = score.getCurrentNotes(SongPart::Melody);
        if (!melodyNotes.empty()) {
            createNoteParticles(tonality, melodyNotes[0].note);
        }
        score.playBeat(instrument);
        if (score.getNumLoops() > 0) {
            score = ScoreGenerator(getRandomTonality()).generate();
        }
    }
}

const std::vector<int> ScorePlayer::getProgression() {
    return chords;
}

void ScorePlayer::setNoteInterval(float noteInterval) {
    this->noteInterval = noteInterval;
}

void ScorePlayer::createChordParticles(Tonality tonality, int chord) {
    for (int i = 0; i < particlesPerChord; ++i) {
        particles.add(Particle(
                -1.f + 3.f * randFloat(),
                -1.f + 3.f * randFloat(),
                0.6f * randFloat() - 0.3f,
                0.6f * randFloat() - 0.3f,
                chordColors[int(tonality)][(chord + Instrument::notesPerOctave * 100) % Instrument::notesPerOctave],
                noteInterval * 4 * 1.5f
        ));
    }
}

void ScorePlayer::createNoteParticles(Tonality tonality, int note) {
    float partX = randFloat();
    float partY = randFloat();
    for (int i = 0; i < particlesPerNote; ++i) {
        particles.add(Particle(
                partX + 0.3f * randFloat() - 0.15f,
                partY + 0.3f * randFloat() - 0.15f,
                0.4f * randFloat() - 0.2f,
                0.4f * randFloat() - 0.2f,
                chordColors[int(tonality)][(note + Instrument::notesPerOctave * 100) % Instrument::notesPerOctave],
                noteInterval * 4 * 1.5f
        ));
    }
}
