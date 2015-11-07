#include "jt_scales.h"
#include "app.h"

#define false 0
#define true 1

typedef signed char bool;

#define PAD_KEY_TYPE_MAJOR 81
#define PAD_KEY_TYPE_MINOR 71

//top row
#define PAD_KEY_SIGNATURE_C 83
#define PAD_KEY_SIGNATURE_G 84
#define PAD_KEY_SIGNATURE_D 85
#define PAD_KEY_SIGNATURE_A 86
#define PAD_KEY_SIGNATURE_E 87
#define PAD_KEY_SIGNATURE_B 88

//second row
#define PAD_KEY_SIGNATURE_F 73
#define PAD_KEY_SIGNATURE_Bb 74
#define PAD_KEY_SIGNATURE_Eb 75
#define PAD_KEY_SIGNATURE_Ab 76
#define PAD_KEY_SIGNATURE_Db 77
#define PAD_KEY_SIGNATURE_Gb 78

#define PAD_KEY_TYPE_COLOUR_ON red
#define PAD_KEY_TYPE_COLOUR_OFF blue
#define PAD_KEY_SIGNATURE_COLOUR_ON green
#define PAD_KEY_SIGNATURE_COLOUR_OFF dark_green

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

typedef struct _PadColour {
  u8 r;
  u8 g;
  u8 b;
} PadColour;

PadColour red = {MAXLED,0,0};
PadColour green = {0,MAXLED,0};
PadColour blue = {0,0,MAXLED};
PadColour dark_green = {0,MAXLED/4,0};

// private function declarations
void set_pad_colour(u8 index, PadColour padColour);
void setup_defaults();
void setup_key_signature_section();
void toggle_major_minor(u8 index);
bool is_in_key_signature_section(u8 index);
bool is_in_key_type_section(u8 index);
void toggle_key_signature(u8 index);

// private functions
void set_pad_colour(u8 index, PadColour padColour)
{
  hal_plot_led(TYPEPAD, index, padColour.r, padColour.g, padColour.b);
}

void setup_defaults()
{
  toggle_major_minor(DEFAULT_KEY_TYPE);
  toggle_key_signature(DEFUALT_KEY_SIGNATURE);
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
  } else { //minor key
    set_pad_colour(PAD_KEY_TYPE_MAJOR, PAD_KEY_TYPE_COLOUR_OFF);
    set_pad_colour(PAD_KEY_TYPE_MINOR, PAD_KEY_TYPE_COLOUR_ON);
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

// public funtions
void jt_handle_pad_event(u8 index, u8 value)
{
  if (is_in_key_type_section(index)) {
    toggle_major_minor(index);
  } else  if (is_in_key_signature_section(index)){
    toggle_key_signature(index);
  }
}

void jt_init()
{
  setup_defaults();
}
