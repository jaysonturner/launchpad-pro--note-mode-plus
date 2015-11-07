#include "jt_scales.h"
#include "bool.h"
#include "grid.h"
#include "pads_and_midi_controller.h"

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
#define PAD_NOTE_RECT_TOP_RIGHT XY_IN_GRID(5,5)

#define PAD_KEY_TYPE_COLOUR_ON blue
#define PAD_KEY_TYPE_COLOUR_OFF dark_blue
#define PAD_KEY_SIGNATURE_COLOUR_ON green
#define PAD_KEY_SIGNATURE_COLOUR_OFF dark_green
#define PAD_LAYOUT_COLOUR_ON white
#define PAD_LAYOUT_COLOUR_OFF grey

#define KEY_SIGNATURE_COUNT 12
u8 key_signature_section[KEY_SIGNATURE_COUNT] = {
  PAD_KEY_SIGNATURE_C,
  PAD_KEY_SIGNATURE_G,
  PAD_KEY_SIGNATURE_D,
  PAD_KEY_SIGNATURE_A,
  PAD_KEY_SIGNATURE_E,
  PAD_KEY_SIGNATURE_B,
  PAD_KEY_SIGNATURE_F,
  PAD_KEY_SIGNATURE_Bb,
  PAD_KEY_SIGNATURE_Eb,
  PAD_KEY_SIGNATURE_Ab,
  PAD_KEY_SIGNATURE_Db,
  PAD_KEY_SIGNATURE_Gb
};

#define DEFAULT_KEY_TYPE PAD_KEY_TYPE_MAJOR
#define DEFUALT_KEY_SIGNATURE PAD_KEY_SIGNATURE_C
#define DEFUALT_LAYOUT PAD_LAYOUT_CHROMATIC

typedef enum _KeyType {
  KeyTypeMajor = 0,
  KeyTypeMinor,
}KeyType;

typedef enum _KeySignature {
  KeySignatureC,
  KeySignatureDb,
  KeySignatureD,
  KeySignatureEb,
  KeySignatureE,
  KeySignatureF,
  KeySignatureGb,
  KeySignatureG,
  KeySignatureAb,
  KeySignatureA,
  KeySignatureBb,
  KeySignatureB
}KeySignature;

typedef enum _Layout {
  LayoutChromatic,
  LayoutInKey
}Layout;

KeyType current_key_type;
KeySignature current_key_signature;
Layout current_layout;

void setup_defaults();
void setup_key_signature_section();

void toggle_major_minor(u8 index);
void toggle_key_signature(u8 index);
void toggle_layout(u8 index);

bool is_in_key_signature_section(u8 index);
bool is_in_key_type_section(u8 index);
bool is_in_layout_section(u8 index);
bool is_in_note_section(u8 index);

// private functions
void setup_defaults()
{
  toggle_major_minor(DEFAULT_KEY_TYPE);
  toggle_key_signature(DEFUALT_KEY_SIGNATURE);
  toggle_layout(DEFUALT_LAYOUT);
}

void setup_key_signature_section()
{
  for (int i = 0; i < KEY_SIGNATURE_COUNT; i++) {
    set_pad_colour(key_signature_section[i], PAD_KEY_SIGNATURE_COLOUR_OFF);
  }
}

void toggle_major_minor(u8 index)
{
  if (index == PAD_KEY_TYPE_MAJOR) {
    set_pad_colour(PAD_KEY_TYPE_MAJOR, PAD_KEY_TYPE_COLOUR_ON);
    set_pad_colour(PAD_KEY_TYPE_MINOR, PAD_KEY_TYPE_COLOUR_OFF);
    current_key_type = KeyTypeMajor;
  } else { //minor key
    set_pad_colour(PAD_KEY_TYPE_MAJOR, PAD_KEY_TYPE_COLOUR_OFF);
    set_pad_colour(PAD_KEY_TYPE_MINOR, PAD_KEY_TYPE_COLOUR_ON);
    current_key_type = KeyTypeMinor;
  }
}

void toggle_layout(u8 index)
{
  if (index == PAD_LAYOUT_CHROMATIC) {
    set_pad_colour(PAD_LAYOUT_CHROMATIC, PAD_LAYOUT_COLOUR_ON);
    set_pad_colour(PAD_LAYOUT_IN_KEY, PAD_LAYOUT_COLOUR_OFF);
    current_layout = LayoutChromatic;
  } else { //in key
    set_pad_colour(PAD_LAYOUT_CHROMATIC, PAD_LAYOUT_COLOUR_OFF);
    set_pad_colour(PAD_LAYOUT_IN_KEY, PAD_LAYOUT_COLOUR_ON);
    current_layout = LayoutInKey;
  }
}

void toggle_key_signature(u8 index)
{
  setup_key_signature_section();
  set_pad_colour(index, PAD_KEY_SIGNATURE_COLOUR_ON);
}

bool is_in_key_signature_section(u8 index)
{
  for (int i = 0; i < KEY_SIGNATURE_COUNT; i++) {
    if (index == key_signature_section[i])
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

// public funtions
void jt_handle_pad_event(u8 index, u8 value)
{
  u8 grid_index = index_to_grid(index);

  if (is_in_key_type_section(grid_index)) {
    toggle_major_minor(grid_index);
  } else  if (is_in_key_signature_section(grid_index)){
    toggle_key_signature(grid_index);
  } else if (is_in_layout_section(grid_index)) {
    toggle_layout(grid_index);
  }
}

void jt_handle_midi_event(u8 index, u8 velocity)
{
  u8 grid_index = index_to_grid(index);

  if (is_in_note_section(grid_index)) {
    send_midi_note_on(grid_index+21, velocity); //A0 for now
  }
}

void jt_init()
{
  setup_defaults();
}
