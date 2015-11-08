#include "jt_scales.h"
#include "bool.h"
#include "grid.h"
#include "pads_and_midi_controller.h"
#include "scale_factory.h"
#include "transpose_handler.h"
#include "key_sig_handler.h"

#define PAD_NOTE_RECT_BOTTOM_LEFT XY_IN_GRID(0,0)
#define PAD_NOTE_RECT_TOP_RIGHT XY_IN_GRID(7,7)

Note *current_layout_grid;
Layout current_layout;

void setup_defaults();
void update_ui();
bool is_in_note_section(u8 index);

// private functions
void setup_defaults()
{
  th_set_key_signature(ksh_get_selected_key_signature());
  th_set_is_minor(0);
  th_set_octave(4);

  current_layout = 0;
}

void update_ui()
{
  current_layout_grid = layout_for_key_signature(th_get_key_signature(),th_get_is_minor(),th_get_octave(),current_layout);

  Note n;
  PadColour colour;
  for (int i = 0; i < 64; i++) {
    n = current_layout_grid[i];
    colour = aqua;

    if (n.is_sharp) {
      colour = black;
    }

    if (n.is_tonic) {
      colour = fuchsia;
    }

    set_pad_colour(i, colour);
  }
}

bool is_in_note_section(u8 index)
{
  return index >= PAD_NOTE_RECT_BOTTOM_LEFT && index <= PAD_NOTE_RECT_TOP_RIGHT;
}


// public funtions
void jt_handle_pad_event(u8 index, u8 value)
{
  if (value == 0) //ignore up state
    return;

  //check outer buttons
  ksh_handle_index(index);
  th_set_key_signature(ksh_get_selected_key_signature());
  th_handle_index(index);

  //update ui
  update_ui();
}

void jt_handle_midi_event(u8 index, u8 velocity)
{
  u8 grid_index = gr_index_to_grid(index);

  if (is_in_note_section(grid_index)) {
    Note note = current_layout_grid[grid_index];
    send_midi_note_on(note.midi_number, velocity);
  }
}

void jt_init()
{
  setup_defaults();
  update_ui();
}
