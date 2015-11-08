#include "jt_scales.h"
#include "bool.h"
#include "grid.h"
#include "pads_and_midi_controller.h"
#include "scale_factory.h"

#define BUTTON_LEFT 93
#define BUTTON_RIGHT 94
#define BUTTON_UP 91
#define BUTTON_DOWN 92

#define PAD_KEY_TYPE_MAJOR XY_IN_GRID(0,7)
#define PAD_KEY_TYPE_MINOR XY_IN_GRID(0,6)

#define PAD_LAYOUT_CHROMATIC XY_IN_GRID(7,7)
#define PAD_LAYOUT_IN_KEY XY_IN_GRID(7,6)

#define PAD_KEY_SIGNATURE_C XY_IN_GRID(1,7)
#define PAD_KEY_SIGNATURE_G XY_IN_GRID(2,7)
#define PAD_KEY_SIGNATURE_D XY_IN_GRID(3,7)
#define PAD_KEY_SIGNATURE_A XY_IN_GRID(4,7)
#define PAD_KEY_SIGNATURE_E XY_IN_GRID(5,7)
#define PAD_KEY_SIGNATURE_B XY_IN_GRID(6,7)

#define PAD_KEY_SIGNATURE_F  XY_IN_GRID(1,6)
#define PAD_KEY_SIGNATURE_Bb XY_IN_GRID(2,6)
#define PAD_KEY_SIGNATURE_Eb XY_IN_GRID(3,6)
#define PAD_KEY_SIGNATURE_Ab XY_IN_GRID(4,6)
#define PAD_KEY_SIGNATURE_Db XY_IN_GRID(5,6)
#define PAD_KEY_SIGNATURE_Gb XY_IN_GRID(6,6)

#define PAD_NOTE_RECT_BOTTOM_LEFT XY_IN_GRID(0,0)
#define PAD_NOTE_RECT_TOP_RIGHT XY_IN_GRID(7,5)

#define PAD_KEY_TYPE_COLOUR_ON blue
#define PAD_KEY_TYPE_COLOUR_OFF dark_blue
#define PAD_KEY_SIGNATURE_COLOUR_ON green
#define PAD_KEY_SIGNATURE_COLOUR_OFF dark_green
#define PAD_LAYOUT_COLOUR_ON white
#define PAD_LAYOUT_COLOUR_OFF grey

#define KEY_SIGNATURE_COUNT 12

u8 key_map[KEY_SIGNATURE_COUNT][KEY_SIGNATURE_COUNT] = {
  {PAD_KEY_SIGNATURE_C,   0},
  {PAD_KEY_SIGNATURE_G,   7},
  {PAD_KEY_SIGNATURE_D,   2},
  {PAD_KEY_SIGNATURE_A,   9},
  {PAD_KEY_SIGNATURE_E,   4},
  {PAD_KEY_SIGNATURE_B,   11},
  {PAD_KEY_SIGNATURE_F,   5},
  {PAD_KEY_SIGNATURE_Bb,  10},
  {PAD_KEY_SIGNATURE_Eb,  3},
  {PAD_KEY_SIGNATURE_Ab,  8},
  {PAD_KEY_SIGNATURE_Db,  1},
  {PAD_KEY_SIGNATURE_Gb,  6}
};

Note *current_layout_grid;

s8 current_key;
u8 current_major_minor;
s8 current_octave;
Layout current_layout;

#define DEFAULT_KEY_TYPE PAD_KEY_TYPE_MAJOR
#define DEFUALT_KEY_SIGNATURE PAD_KEY_SIGNATURE_C
#define DEFUALT_LAYOUT PAD_LAYOUT_CHROMATIC

void setup_defaults();
void setup_key_signature_section();
void setup_layout();

void toggle_major_minor(u8 index);
void toggle_key_signature(u8 index);
void toggle_layout(u8 index);

bool is_in_key_signature_section(u8 index);
bool is_in_key_type_section(u8 index);
bool is_in_layout_section(u8 index);
bool is_in_note_section(u8 index);
bool is_in_transpose_section(u8 index);

u8 note_number_for_key_sig_index(u8 index);
void handle_transpose(u8 index);

// private functions
void setup_defaults()
{
  toggle_major_minor(DEFAULT_KEY_TYPE);
  toggle_key_signature(DEFUALT_KEY_SIGNATURE);
  toggle_layout(DEFUALT_LAYOUT);

  current_key = note_number_for_key_sig_index(DEFUALT_KEY_SIGNATURE);
  current_layout = 0;
  current_major_minor = 0;
  current_octave = 4;

  setup_layout();
}

void setup_layout()
{
  current_layout_grid = layout_for_key_signature(current_key,current_major_minor,current_octave,current_layout);

  Note n;
  PadColour colour;
  for (int i = 0; i < 48; i++) {
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

void setup_key_signature_section()
{
  for (int i = 0; i < KEY_SIGNATURE_COUNT; i++) {
    set_pad_colour(key_map[i][0], PAD_KEY_SIGNATURE_COLOUR_OFF);
  }
}

void toggle_major_minor(u8 index)
{
  if (index == PAD_KEY_TYPE_MAJOR) {
    set_pad_colour(PAD_KEY_TYPE_MAJOR, PAD_KEY_TYPE_COLOUR_ON);
    set_pad_colour(PAD_KEY_TYPE_MINOR, PAD_KEY_TYPE_COLOUR_OFF);
  } else { //minor key
    set_pad_colour(PAD_KEY_TYPE_MAJOR, PAD_KEY_TYPE_COLOUR_OFF);
    set_pad_colour(PAD_KEY_TYPE_MINOR, PAD_KEY_TYPE_COLOUR_ON);
  }
}

void toggle_layout(u8 index)
{
  if (index == PAD_LAYOUT_CHROMATIC) {
    set_pad_colour(PAD_LAYOUT_CHROMATIC, PAD_LAYOUT_COLOUR_ON);
    set_pad_colour(PAD_LAYOUT_IN_KEY, PAD_LAYOUT_COLOUR_OFF);
  } else { //in key
    set_pad_colour(PAD_LAYOUT_CHROMATIC, PAD_LAYOUT_COLOUR_OFF);
    set_pad_colour(PAD_LAYOUT_IN_KEY, PAD_LAYOUT_COLOUR_ON);
  }
}

void toggle_key_signature(u8 index)
{
  current_key = note_number_for_key_sig_index(index);

  setup_layout();
  setup_key_signature_section();
  set_pad_colour(index, PAD_KEY_SIGNATURE_COLOUR_ON);
}

u8 note_number_for_key_sig_index(u8 index)
{
  for (int i = 0; i < KEY_SIGNATURE_COUNT; i++) {
    if (index == key_map[i][0])
      return key_map[i][1];
  }
  return 0;
}

bool is_in_key_signature_section(u8 index)
{
  for (int i = 0; i < KEY_SIGNATURE_COUNT; i++) {
    if (index == key_map[i][0])
      return true;
  }
  return false;
}

bool is_in_key_type_section(u8 index)
{
  return index == PAD_KEY_TYPE_MAJOR || index == PAD_KEY_TYPE_MINOR;
}

bool is_in_layout_section(u8 index)
{
  return index == PAD_LAYOUT_CHROMATIC || index == PAD_LAYOUT_IN_KEY;
}

bool is_in_note_section(u8 index)
{
  return index >= PAD_NOTE_RECT_BOTTOM_LEFT && index <= PAD_NOTE_RECT_TOP_RIGHT;
}

bool is_in_transpose_section(u8 index)
{
  return index == BUTTON_UP || index == BUTTON_DOWN
        || index == BUTTON_LEFT || index == BUTTON_RIGHT;
}

void handle_transpose(u8 index)
{
  switch (index) {
    case BUTTON_UP:
      current_octave++;
      break;
    case BUTTON_DOWN:
      current_octave--;
      break;
    case BUTTON_RIGHT:
      current_key++;
      break;
    case BUTTON_LEFT:
      current_key--;
      break;
    default:
      break;
  }

  if (current_key > 11) {
    current_key = 11;
  }

  if (current_key < 0) {
    current_key = 0;
  }

  if (current_octave > 10) {
    current_octave = 10;
  }

  if (current_octave < 0) {
    current_octave = 0;
  }

  setup_layout();
}


// public funtions
void jt_handle_pad_event(u8 index, u8 value)
{
  //check main grid
  u8 grid_index = index_to_grid(index);
  if (is_in_key_type_section(grid_index)) {
    toggle_major_minor(grid_index);
  } else  if (is_in_key_signature_section(grid_index)){
    toggle_key_signature(grid_index);
  } else if (is_in_layout_section(grid_index)) {
    toggle_layout(grid_index);
  }

  if (value == 0) //ignore up state
    return;

  //check outer buttons
  if (is_in_transpose_section(index)) {
    handle_transpose(index);
  }
}

void jt_handle_midi_event(u8 index, u8 velocity)
{
  u8 grid_index = index_to_grid(index);

  if (is_in_note_section(grid_index)) {
    Note note = current_layout_grid[grid_index];
    send_midi_note_on(note.midi_number, velocity);
  }
}

void jt_init()
{
  setup_defaults();
}
