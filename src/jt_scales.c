#include "jt_scales.h"
#include "app.h"

#define false 0
#define true 1

typedef signed char bool;

#define PAD_MAJOR_KEY 82
#define PAD_MINOR_KEY 72

#define PAD_KEY_COLOUR_ON red
#define PAD_KEY_COLOUR_OFF blue

typedef struct _PadColour {
  u8 r;
  u8 g;
  u8 b;
} PadColour;

PadColour red = {MAXLED,0,0};
PadColour green = {0,MAXLED,0};
PadColour blue = {0,0,MAXLED};

// private function declarations
void set_pad_colour(u8 index, PadColour padColour);
void setup_grid_colours();
void toggle_major_minor(u8 major_minor);

// private functions
void set_pad_colour(u8 index, PadColour padColour)
{
  hal_plot_led(TYPEPAD, index, padColour.r, padColour.g, padColour.b);
}

void setup_grid_colours()
{
  toggle_major_minor(PAD_MAJOR_KEY);
}

void toggle_major_minor(u8 major_minor)
{
  if (major_minor == PAD_MAJOR_KEY) {
    set_pad_colour(PAD_MAJOR_KEY, PAD_KEY_COLOUR_ON);
    set_pad_colour(PAD_MINOR_KEY, PAD_KEY_COLOUR_OFF);
  } else { //minor key
    set_pad_colour(PAD_MAJOR_KEY, PAD_KEY_COLOUR_OFF);
    set_pad_colour(PAD_MINOR_KEY, PAD_KEY_COLOUR_ON);
  }
}

bool is_in_key_signature_grid(u8 index)
{
  return false;
}

// public funtions
void jt_handle_pad_event(u8 index, u8 value)
{
  if (index == PAD_MAJOR_KEY) {
      toggle_major_minor(PAD_MAJOR_KEY);
  } else if (index == PAD_MINOR_KEY) {
      toggle_major_minor(PAD_MINOR_KEY);
  } else  if (is_in_key_signature_grid(index)){

  }
}

void jt_init()
{
  setup_grid_colours();
}
