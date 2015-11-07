#ifndef PADS_AND_MIDI_CONTROLLER_H
#define PADS_AND_MIDI_CONTROLLER_H

#include "app_defs.h"

typedef struct _PadColour {
  u8 r;
  u8 g;
  u8 b;
} PadColour;

extern PadColour red;
extern PadColour green;
extern PadColour blue;
extern PadColour dark_green;
extern PadColour dark_blue;
extern PadColour white;
extern PadColour grey;
extern PadColour black;
extern PadColour fuchsia;
extern PadColour aqua;

void set_pad_colour(u8 index, PadColour padColour);
void send_midi_note_on(u8 note_number, u8 velocity);

PadColour pad_colour_make(u8 r, u8 g, u8 b);

#endif
