#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include "../Instrument.hpp"

struct Note {
    int note;
    float volume;
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
class MusicScore {
public:
    /**
     * Play one beat of the song on the instrument
     * @param instrument Instrument to play notes on
     */
    void playBeat(Instrument &instrument);

    /**
     * Add a new note to the song of the given song part
     * @param part Song part to add note under
     * @param note Note number to play (leave empty for a rest)
     * @param volume Volume of note to play
     */
    void add(SongPart part, int note = Instrument::restNote, float volume = 1.f);

    /**
     * Add a new array of notes to be played at the next beat for the given part
     * @param part Song part to add notes under
     * @param notes Note numbers to play
     * @param volume Volume of notes to play
     */
    void add(SongPart part, const std::vector<int> &notes, float volume = 1.f);

    /**
     * Get the current notes for the given song part at the current beat
     * @param part Song part to get notes of
     * @param checkBeat Whether to return nothing if the song part isn't played on the current beat
     * @return Array of note objects
     */
    const std::vector<Note> &getCurrentNotes(SongPart part, bool checkBeat = true);

private:
    static const std::vector<Note> noNotes;
    std::deque<std::vector<Note>> &getPart(SongPart part);

    std::deque<std::vector<Note>> parts[numSongParts];
    int timeTillBeat[numSongParts]{};
    int beatNum = 0;
};
