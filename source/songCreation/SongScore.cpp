#include "SongScore.hpp"

const std::vector<Note> SongScore::noNotes;

void SongScore::updateBeat(Instrument &instrument) {
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

void SongScore::add(SongPart part, int note, float volume) {
    if (note == Instrument::restNote) {
        add(part, std::vector<int>({}), volume);
    } else {
        add(part, std::vector<int>({note}), volume);
    }
}

void SongScore::add(SongPart part, const std::vector<int> &notes, float volume) {
    std::vector<Note> fullNotes;
    fullNotes.reserve(notes.size());
    for (int i : notes) {
        fullNotes.push_back({i, volume});
    }
    getPart(part).push_back(fullNotes);
}

const std::vector<Note> &SongScore::getCurrentNotes(SongPart part, bool checkBeat) {
    if (checkBeat && timeTillBeat[int(part)] != 0) {
        return noNotes;
    }
    auto &partLine = parts[int(part)];
    return partLine[(beatNum / beatsPerSongPart[int(part)]) % partLine.size()];
}

std::deque<std::vector<Note>> &SongScore::getPart(SongPart part) {
    return parts[int(part)];
}
