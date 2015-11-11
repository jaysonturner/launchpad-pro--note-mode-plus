// Using this file to test that the keyboard grids
// are created correctly

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scale_factory.h"

const char *octave_zero_note_lookup[12] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
const int octave_zero_midi_lookup[12] =   {0,1,2,3,4,5,6,7,8,9,10,11};

char *c_major_in_key[64] = {
  "C","D","E","F","G","A","B","C",
  "F","G","A","B","C","D","E","F",
  "B","C","D","E","F","G","A","B",
  "E","F","G","A","B","C","D","E",
  "A","B","C","D","E","F","G","A",
  "D","E","F","G","A","B","C","D",
  "G","A","B","C","D","E","F","G",
  "C","D","E","F","G","A","B","C"
};

int c_major_in_key_octaves[64] = {
  0,0,0,0,0,0,0,1,
  0,0,0,0,1,1,1,1,
  0,1,1,1,1,1,1,1,
  1,1,1,1,1,2,2,2,
  1,1,2,2,2,2,2,2,
  2,2,2,2,2,2,3,3,
  2,2,2,3,3,3,3,3,
  3,3,3,3,3,3,3,4
};

int midi_number_for_note(const char *note, int octave)
{
  for (int i = 0; i < 12; i++) {
    if(0 == strcmp(octave_zero_note_lookup[i],note)) {
      return octave_zero_midi_lookup[i] + (octave * 12);
    }
  }
  return 0;
}

int testCMajorInKey(char **msg, int octave)
{
  *msg = "testCMajorInKey";
  Note *layout = layout_for_key_signature(0,0,octave,2);

  for (int i = 0; i < 64; i++) {
    Note n = layout[i];
    int expected_midi = midi_number_for_note(c_major_in_key[i],c_major_in_key_octaves[i]+octave);
    printf("expected %d %s%d, actual %d\n", expected_midi, c_major_in_key[i],c_major_in_key_octaves[i]+octave, n.midi_number );
    if (expected_midi != n.midi_number) {
      return 0;
    }
  }

  return 1;
}

int testGSharpIs104(char **msg)
{
  *msg = "testGSharpIs104";
  int n = midi_number_for_note("G#", 8);
  return n == 104;
}

int testCIs0(char **msg)
{
  *msg = "testCIs0";
  int n = midi_number_for_note("C", 0);
  return n == 0;
}

int main(int argc, char const *argv[]) {

  char *msg;
  printf("%s - %s\n",testGSharpIs104(&msg) ? "passed" : "failed", msg);
  printf("%s - %s\n",testCIs0(&msg) ? "passed" : "failed", msg);
  printf("%s - %s\n",testCMajorInKey(&msg, 0) ? "passed" : "failed", msg);
  printf("%s - %s\n",testCMajorInKey(&msg, 5) ? "passed" : "failed", msg);

  return 0;
}
