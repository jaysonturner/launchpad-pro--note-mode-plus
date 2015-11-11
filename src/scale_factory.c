#include "scale_factory.h"
#include <stdlib.h>

#define GRID_WH 8
#define MAX_NUMBER_OF_NOTES 64
#define OCTAVE_LENGTH 12
#define SCALE_LENGTH 7

//upside down to physical layout
int inkey_degree_map[8][8] = {
  {1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 },//0
  {4 ,5 ,6 ,7 ,8 ,9 ,10,11},//1
  {7 ,8 ,9 ,10,11,12,13,14},//2
  {10,11,12,13,14,15,16,17},//3
  {13,14,15,16,17,18,19,20},//4
  {16,17,18,19,20,21,22,23},//5
  {19,20,21,22,23,24,25,26},//6
  {22,23,24,25,26,27,28,29},//7
};

char chromatic_notes[OCTAVE_LENGTH]   = {'C','C','D','D','E','F','F','G','G','A','A','B'};
char chromatic_pattern[OCTAVE_LENGTH] = {'n','#','n','#','n','n','#','n','#','n','#','n'};

int scale_major[7] = {0,2,4,5,7,9,11};
int scale_minor[7] = {0,2,3,5,7,8,10};
int scale_dorian[7] = {0,2,3,5,7,9,10};
int scale_myxolydian[7] = {0,2,4,5,7,9,10};
int scale_lydian[7] = {0,2,4,6,7,9,11};

// 'Phrygian', [0, 1, 3, 5, 7, 8, 10],
// 'Locrian', [0, 1, 3, 5, 6, 8, 10],
// 'Diminished', [0, 1, 3, 4, 6, 7, 9, 10],
// 'Whole-half', [0, 2, 3, 5, 6, 8, 9, 11],
// 'Whole Tone', [0, 2, 4, 6, 8, 10],
// 'Minor Blues', [0,3, 5, 6, 7, 10],
// 'Minor Pentatonic', [0, 3, 5, 7, 10],
// 'Major Pentatonic', [0,2, 4, 7, 9],
// 'Harmonic Minor', [0, 2, 3, 5, 7, 8, 11],
// 'Melodic Minor', [0, 2, 3, 5, 7, 9, 11],
// 'Super Locrian', [0, 1, 3, 4, 6, 8, 10],
// 'Bhairav', [0, 1, 4, 5, 7, 8, 11],
// 'Hungarian Minor', [0, 2, 3, 6, 7, 8, 11],
// 'Minor Gypsy', [0, 1, 4, 5, 7, 8, 10],
// 'Hirojoshi', [0, 2, 3, 7, 8],
// 'In-Sen', [0, 1, 5, 7, 10],
// 'Iwato', [0, 1, 5, 6, 10],
// 'Kumoi', [0, 2, 3, 7, 9],
// 'Pelog', [0, 1, 3, 4, 7, 8],
// 'Spanish', [0,1,3,4,5,6,8,10]]

Note returnable_layout[MAX_NUMBER_OF_NOTES];

int midi_for_degree(int degree, int *scale)
{
  int d = degree;
  int midi = 0;

  while (d > 6) {
    d = d - 7;
    midi += OCTAVE_LENGTH;
  }

  return scale[d] + midi;
}

bool are_tonal_equivalent(Note *note1, Note* note2)
{
  return (note1->note == note2->note) && (note1->is_sharp == note2->is_sharp);
}

Note note_for_note_number(u8 note_number)
{
  int nearest_c = note_number - (note_number % OCTAVE_LENGTH);
  int normalised_note = note_number - nearest_c;

  Note n;
  n.midi_number = note_number;
  n.is_sharp = (chromatic_pattern[normalised_note] == '#');
  n.note = chromatic_notes[normalised_note];
  n.octave = (nearest_c / OCTAVE_LENGTH) - 2; //anchored at C-2 (midi 0)

  return n;
}

Note* unfixed_chromatic(u8 starting_note_number)
{
  Note starting_note = note_for_note_number(starting_note_number);
  u8 note_number = starting_note_number;

  for (int i = 0; i < GRID_WH; i++) {
    note_number = i + starting_note_number;

    for (int j = 0; j < GRID_WH; j++) {
      int index = i + (j * GRID_WH);
      Note n = note_for_note_number(note_number);
      n.is_tonic = are_tonal_equivalent(&n, &starting_note);
      returnable_layout[index] = n;

      note_number += 5;
    }
  }

  return returnable_layout;
}

Note* fixed_chromatic(u8 starting_note_number)
{
  Note *unfixed_chromatic_in_c = unfixed_chromatic(0);

  Note starting_note = note_for_note_number(starting_note_number);
  u8 note_number = starting_note_number;

  for (int i = 0; i < GRID_WH; i++) {
    note_number = i + starting_note_number;

    for (int j = 0; j < GRID_WH; j++) {
      int index = i + (j * GRID_WH);

      Note n = note_for_note_number(note_number);

      Note un = unfixed_chromatic_in_c[index];

      un.midi_number = n.midi_number;
      un.is_fixed_tonic = are_tonal_equivalent(&un, &starting_note);
      returnable_layout[index] = un;

      note_number += 5;
    }
  }

  return returnable_layout;
}

Note* chromatic_layout(u8 starting_note_number, bool fixed)
{
  Note *layout;

  // I hate the way I make this fixed layout, but it works for now.
  // very smelly.
  if (fixed) {
    layout = fixed_chromatic(starting_note_number);
  } else {
    layout = unfixed_chromatic(starting_note_number);
  }

  return layout;
}

Note* inkey_layout(u8 starting_note_number, int *scale)
{
  Note starting_note = note_for_note_number(starting_note_number);
  u8 note_number = starting_note_number;

  int degree = 0;
  for (int i = 0; i < GRID_WH; i++) {
    for (int j = 0; j < GRID_WH; j++) {
      int index = i + (j * GRID_WH);

      degree = inkey_degree_map[j][i]-1;
      note_number = midi_for_degree(degree, scale) + starting_note_number;

      Note n = note_for_note_number(note_number);
      n.is_tonic = are_tonal_equivalent(&n, &starting_note);
      returnable_layout[index] = n;
    }
  }

  return returnable_layout;
}

Note* layout_for_key_signature(u8 note, ScaleType scale_type, u8 octave, Layout layout_style)
{
  u8 starting_note = (note + (octave * OCTAVE_LENGTH));

  int *scale = scale_major;

  if (scale_type == ScaleTypeMinor) {
    scale = scale_minor;
  }

  if (layout_style == LayoutChromatic || layout_style == LayoutChromaticFixed) {
    return chromatic_layout(starting_note, layout_style == LayoutChromaticFixed);
  } else {
    return inkey_layout(starting_note, scale);
  }
}
