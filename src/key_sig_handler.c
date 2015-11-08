#include "key_sig_handler.h"
#include "pads_and_midi_controller.h"

#define BUTTON_KEY_SIGNATURE_C 89
#define BUTTON_KEY_SIGNATURE_G 79
#define BUTTON_KEY_SIGNATURE_D 69
#define BUTTON_KEY_SIGNATURE_A 59
#define BUTTON_KEY_SIGNATURE_E 49
#define BUTTON_KEY_SIGNATURE_B 39

#define BUTTON_KEY_SIGNATURE_F  80
#define BUTTON_KEY_SIGNATURE_Bb 70
#define BUTTON_KEY_SIGNATURE_Eb 60
#define BUTTON_KEY_SIGNATURE_Ab 50
#define BUTTON_KEY_SIGNATURE_Db 40
#define BUTTON_KEY_SIGNATURE_Gb 30

#define KEY_SIGNATURE_COUNT 12

int key_map[KEY_SIGNATURE_COUNT][KEY_SIGNATURE_COUNT] = {
  {BUTTON_KEY_SIGNATURE_C,   0},
  {BUTTON_KEY_SIGNATURE_G,   7},
  {BUTTON_KEY_SIGNATURE_D,   2},
  {BUTTON_KEY_SIGNATURE_A,   9},
  {BUTTON_KEY_SIGNATURE_E,   4},
  {BUTTON_KEY_SIGNATURE_B,   11},
  {BUTTON_KEY_SIGNATURE_F,   5},
  {BUTTON_KEY_SIGNATURE_Bb,  10},
  {BUTTON_KEY_SIGNATURE_Eb,  3},
  {BUTTON_KEY_SIGNATURE_Ab,  8},
  {BUTTON_KEY_SIGNATURE_Db,  1},
  {BUTTON_KEY_SIGNATURE_Gb,  6}
};

int currently_selected_key = 0;

int note_number_for_key_sig_index(int index);
void update_buttons(int index);

int note_number_for_key_sig_index(int index)
{
  for (int i = 0; i < KEY_SIGNATURE_COUNT; i++) {
    if (index == key_map[i][0])
      return key_map[i][1];
  }
  return -1;
}

void update_buttons(int index)
{
  for (int i = 0; i < KEY_SIGNATURE_COUNT; i++) {
    if (key_map[i][0] == index) {
      set_pad_colour(index, green);
    } else {
      set_pad_colour(key_map[i][0], white);
    }
  }
}

void ksh_init()
{
  ksh_handle_index(BUTTON_KEY_SIGNATURE_C);
}

void ksh_handle_index(int index)
{
  int note = note_number_for_key_sig_index(index);

  if(note == -1)
    return;

  currently_selected_key = note;
  update_buttons(index);
}

int ksh_get_selected_key_signature()
{
  return currently_selected_key;
}
