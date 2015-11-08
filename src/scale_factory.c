#include "scale_factory.h"
#include <string.h>

#define MAX_NUMBER_OF_NOTES 64
#define OCTAVE_LENGTH 12

// char *key_lookup_sharps[OCTAVE_LENGTH] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
// char *key_lookup_flats[OCTAVE_LENGTH]  = {"C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B"};

char chromatic_notes[OCTAVE_LENGTH]   = {'C','C','D','D','E','F','F','G','G','A','A','B'};
char chromatic_pattern[OCTAVE_LENGTH] = {'n','#','n','#','n','n','#','n','#','n','#','n'};

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

Note* chromatic_layout(u8 starting_note_number)
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

Note* layout_for_key_signature(u8 note, u8 major_minor, u8 octave, Layout layout_style)
{
  u8 starting_note = (note + (octave * 12));
  return chromatic_layout(starting_note);
}
