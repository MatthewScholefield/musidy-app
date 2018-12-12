#pragma once

/**
 * Find the note closest to another note, ignoring octaves
 * @param note Scale degree (without octave)
 * @param source Note to map to
 * @return Scale degree offset by some octaves
 */
int closestNote(int note, int source);

int upperNoteTo(int t, int note);
int lowerNoteTo(int t, int note);

