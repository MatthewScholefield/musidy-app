#pragma once

/**
 * Find the note closest to another note, ignoring octaves
 * @param note Scale degree (without octave)
 * @param source Note to map to
 * @return Scale degree offset by some octaves
 */
int closestNote(int note, int source);

/**
 * Find the scale degree above the given note
 * @param degree Scale degree
 * @param note Note to compare to
 * @return Note of scale degree closest to other note
 */
int upperNoteTo(int degree, int note);

/**
 * Find the scale degree below the given note
 * @param degree Scale degree
 * @param note Note to compare to
 * @return Note of scale degree closest to other note
 */
int lowerNoteTo(int degree, int note);
