#include "scale_factory.h"

#define MAX_NUMBER_OF_NOTES 48
#define OCTAVE_LENGTH 12

char chromatic_notes[OCTAVE_LENGTH]   = {'C','C','D','D','E','F','F','G','G','A','A','B'};
char chromatic_pattern[OCTAVE_LENGTH] = {'n','#','n','#','n','n','#','n','#','n','#','n'};

Note returnable_layout[MAX_NUMBER_OF_NOTES];

Note note_for_note_number(u8 note_number)
{
  int nearest_c = note_number - (note_number % 12);
  int normalised_note = note_number - nearest_c;

  Note n;
  n.midi_number = note_number;
  n.is_sharp = (chromatic_pattern[normalised_note] == '#');
  n.is_tonic = (normalised_note == 0);
  n.note = chromatic_notes[normalised_note];
  n.octave = (nearest_c / 12) - 2; //anchored at C-2 (midi 0)

  return n;
}

Note* chromatic_layout(u8 starting_note_number)
{
  u8 note_number = starting_note_number;

  for (int i = 0; i < 8; i++) {
    note_number = i + starting_note_number;

    for (int j = 0; j < 6; j++) {
      int index = i + (j * 8);
      returnable_layout[index] = note_for_note_number(note_number);
      note_number += 5;
    }
  }

  return returnable_layout;
}

Note* layout_for_key_signature(KeySignature key, KeyType type, u8 octave, Layout layout_style)
{
  u8 c_minus_2 = 0;

  return chromatic_layout(24);
}

// u8 midi_value_for_note(char *note_name)
// {
//   int len = strlen(note_name);
//
//   if (len == 2) { //natural (A0)
//     char note = note_name[0];
//     int
//   } else if (len == 3) { //flat/sharp (A#0)
//
//   }
//
//   return 0;
// }

// Note* layout_for_key_signature(KeySignature key, KeyType type, Layout layout_style)
// {
//   int midi_number = 0;
//   int degree_count = 0;
//   Note n;
//
//   for (int i = 0; i < MAX_NUMBER_OF_NOTES; i++) {
//     bool is_sharp = (chromatic[degree_count] == '#');
//
//     n.midi_number = midi_number;
//     n.is_tonic = false;
//     n.is_sharp = is_sharp;
//
//     if (degree_count == OCTAVE_LENGTH || degree_count == 0) {
//       n.is_tonic = true;
//       degree_count = 0;
//     }
//
//     midi_number++;
//     degree_count++;
//
//     returnable_layout[i] = n;
//   }
//
//   return returnable_layout;
// }
