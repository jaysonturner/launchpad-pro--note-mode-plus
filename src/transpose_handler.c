#include "transpose_handler.h"
#include "pads_and_midi_controller.h"

// #define BUTTON_LEFT 93
// #define BUTTON_RIGHT 94
#define BUTTON_UP 91
#define BUTTON_DOWN 92

int current_key_signature = 0;
int current_is_minor = 0;
int current_octave = 0;

int is_in_transpose_section(int index);
void valididate_transpose();
void update();

int is_in_transpose_section(int index)
{
  return index == BUTTON_UP || index == BUTTON_DOWN;
        // || index == BUTTON_LEFT || index == BUTTON_RIGHT;
}

void valididate_transpose()
{
  if (current_key_signature > 11) {
    current_key_signature = 11;
  }

  if (current_key_signature < 0) {
    current_key_signature = 0;
  }

  if (current_octave > 10) {
    current_octave = 10;
  }

  if (current_octave < 0) {
    current_octave = 0;
  }
}

void update()
{
  set_pad_colour(BUTTON_UP, blue);
  set_pad_colour(BUTTON_DOWN, blue);
}

void th_handle_index(int index)
{
  if(!is_in_transpose_section(index))
    return;

  switch (index) {
    case BUTTON_UP:
      current_octave++;
      break;
    case BUTTON_DOWN:
      current_octave--;
      break;
    // case BUTTON_RIGHT:
    //   current_key_signature++;
    //   break;
    // case BUTTON_LEFT:
    //   current_key_signature--;
    //   break;
    default:
      break;
  }
  valididate_transpose();
}

void th_init()
{
  update();
}

void th_set_octave(int octave)
{
  current_octave = octave;
  valididate_transpose();
}

void th_set_is_minor(int minor)
{
  current_is_minor = minor;
  valididate_transpose();
}

void th_set_key_signature(int key_signature)
{
  current_key_signature = key_signature;
  valididate_transpose();
}

int th_get_octave()
{
  return current_octave;
}

int th_get_is_minor()
{
  return current_is_minor;
}

int th_get_key_signature()
{
  return current_key_signature;
}
