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
 * @param note Note to compare to
 * @param degree Scale degree
 * @return Note of scale degree closest to other note
 */
int upperNoteTo(int note, int degree);

/**
 * Find the scale degree below the given note
 * @param note Note to compare to
 * @param degree Scale degree
 * @return Note of scale degree closest to other note
 */
int lowerNoteTo(int note, int degree);

/**
 * Return the scale degree of a note from 0 to 6
 * @param note Note (possibly in another octave)
 * @return Scale degree
 */
int getDegree(int note);

