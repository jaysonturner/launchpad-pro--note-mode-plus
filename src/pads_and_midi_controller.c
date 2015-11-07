#include "pads_and_midi_controller.h"
#include "grid.h"
#include "app.h"

PadColour red = {MAXLED,0,0};
PadColour green = {0,MAXLED,0};
PadColour blue = {0,0,MAXLED};
PadColour dark_green = {0,MAXLED/4,0};
PadColour dark_blue = {0,0,MAXLED/4};
PadColour white = {MAXLED,MAXLED,MAXLED};
PadColour grey = {MAXLED/4,MAXLED/4,MAXLED/4};

void set_pad_colour(u8 grid_index, PadColour padColour)
{
  hal_plot_led(TYPEPAD, grid_to_index(grid_index), padColour.r, padColour.g, padColour.b);
}

void send_midi_note_on(u8 note_number, u8 velocity)
{
  hal_send_midi(DINMIDI, NOTEON | 0, note_number, velocity);
  hal_send_midi(USBSTANDALONE, NOTEON | 0, note_number, velocity);
}

PadColour pad_colour_make(u8 r, u8 g, u8 b)
{
  return (PadColour){r,g,b};
}
