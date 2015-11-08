#include "scale_factory.h"
#include <stdlib.h>

#define MAX_NUMBER_OF_NOTES 64
#define OCTAVE_LENGTH 12
#define SCALE_LENGTH 7

// char *key_lookup_sharps[OCTAVE_LENGTH] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
// char *key_lookup_flats[OCTAVE_LENGTH]  = {"C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B"};

char chromatic_notes[OCTAVE_LENGTH]   = {'C','C','D','D','E','F','F','G','G','A','A','B'};
char chromatic_pattern[OCTAVE_LENGTH] = {'n','#','n','#','n','n','#','n','#','n','#','n'};

int scale_major[SCALE_LENGTH] = {0,2,4,5,7,9,11};

Note returnable_layout[MAX_NUMBER_OF_NOTES];

bool are_tonal_equivalent(Note *note1, Note* note2)
{
  return (note1->note == note2->note) && (note1->is_sharp == note2->is_sharp);
}

Note note_for_note_number(u8 note_number)
{
  int nearest_c = note_number - (note_number % 12);
  int normalised_note = note_number - nearest_c;

  Note n;
  n.midi_number = note_number;
  n.is_sharp = (chromatic_pattern[normalised_note] == '#');
  n.note = chromatic_notes[normalised_note];
  n.octave = (nearest_c / 12) - 2; //anchored at C-2 (midi 0)

  return n;
}

Note* unfixed_chromatic(u8 starting_note_number)
{
  Note starting_note = note_for_note_number(starting_note_number);
  u8 note_number = starting_note_number;

  for (int i = 0; i < 8; i++) {
    note_number = i + starting_note_number;

    for (int j = 0; j < 8; j++) {
      int index = i + (j * 8);
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

  for (int i = 0; i < 8; i++) {
    note_number = i + starting_note_number;

    for (int j = 0; j < 8; j++) {
      int index = i + (j * 8);

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

Note* inkey_layout(u8 starting_note_number)
{
  Note starting_note = note_for_note_number(starting_note_number);
  u8 note_number = starting_note_number;


  int x_degree = 0;
  int y_degree = 0;
  for (int i = 0; i < 8; i++) {
    note_number = scale_major[x_degree] + starting_note_number;
    y_degree = x_degree;

    for (int j = 0; j < 8; j++) {
      int index = i + (j * 8);

      Note n = note_for_note_number(note_number);
      n.is_tonic = are_tonal_equivalent(&n, &starting_note);
      returnable_layout[index] = n;

      int old_y_degree = y_degree;

      y_degree+=3;

      if (y_degree > 6) {
        y_degree = y_degree-7;
      }

      int interval;

      if (y_degree < old_y_degree){
        interval = (abs(scale_major[old_y_degree] - scale_major[y_degree]))-2;
      } else {
        interval = abs(scale_major[old_y_degree] - scale_major[y_degree]);
      }

      note_number += interval;
    }

    x_degree++;

    if (x_degree > 6) {
      x_degree = 0;
    }
  }

  return returnable_layout;
}

Note* layout_for_key_signature(u8 note, u8 major_minor, u8 octave, Layout layout_style)
{
  u8 starting_note = (note + (octave * 12));

  if (layout_style == LayoutChromatic || layout_style == LayoutChromaticFixed) {
    return chromatic_layout(starting_note, layout_style == LayoutChromaticFixed);
  } else {
    return inkey_layout(starting_note);
  }
}
