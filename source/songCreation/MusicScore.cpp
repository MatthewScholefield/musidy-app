#include "MusicScore.hpp"

const std::vector<Note> MusicScore::noNotes;

void MusicScore::playBeat(Instrument &instrument) {
    for (int part = 0; part < numSongParts; ++part) {
        --timeTillBeat[part];
        if (timeTillBeat[part] < 0 && !parts[part].empty()) {
            timeTillBeat[part] += beatsPerSongPart[part];
            for (Note note : getCurrentNotes(SongPart(part), false)) {
                instrument.play(note.note, note.volume);
            }
        }
    }
    ++beatNum;
}

void MusicScore::add(SongPart part, int note, float volume) {
    if (note == Instrument::restNote) {
        add(part, std::vector<int>({}), volume);
    } else {
        add(part, std::vector<int>({note}), volume);
    }
}

void MusicScore::add(SongPart part, const std::vector<int> &notes, float volume) {
    std::vector<Note> fullNotes;
    fullNotes.reserve(notes.size());
    for (int i : notes) {
        fullNotes.push_back({i, volume});
    }
    getPart(part).push_back(fullNotes);
}

const std::vector<Note> &MusicScore::getCurrentNotes(SongPart part, bool checkBeat) {
    if (checkBeat && timeTillBeat[int(part)] != 0) {
        return noNotes;
    }
    auto &partLine = parts[int(part)];
    return partLine[(beatNum / beatsPerSongPart[int(part)]) % partLine.size()];
}

std::deque<std::vector<Note>> &MusicScore::getPart(SongPart part) {
    return parts[int(part)];
}
