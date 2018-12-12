#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include "../Instrument.hpp"

struct Note {
    int note;
    float volume = 1.f;
};

enum class SongPart : int {
    Bass = 0,
    Chords,
    Harmony,
    Melody
};
static constexpr int numSongParts = 4;
static constexpr int beatsPerSongPart[numSongParts] = {
        4,
        4,
        1,
        1
};

/**
 * Represents all notes in song
 */
class SongScore {
public:
    void updateBeat(Instrument &instrument);

    void add(SongPart part, int note = Instrument::restNote, float volume = 1.f);

    void add(SongPart part, const std::vector<int> &notes, float volume = 1.f);

    const std::vector<Note> &getCurrentNotes(SongPart part, bool checkBeat = true);

private:
    static const std::vector<Note> noNotes;
    std::deque<std::vector<Note>> &getPart(SongPart part);

    std::deque<std::vector<Note>> parts[numSongParts];
    int timeTillBeat[numSongParts]{};
    int beatNum = 0;
};
