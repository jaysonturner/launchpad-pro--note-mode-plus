#include "layout_handler.h"
#include "pads_and_midi_controller.h"

#define BUTTON_CHROMATIC_FIXED 95
#define BUTTON_CHROMATIC_UNFIXED 96

int button_layout_map[2][2] = {
  {BUTTON_CHROMATIC_FIXED,LayoutChromaticFixed},
  {BUTTON_CHROMATIC_UNFIXED,LayoutChromatic}
};

Layout current_layout = LayoutChromaticFixed;

int is_in_layout_section(int index)
{
  return index == BUTTON_CHROMATIC_FIXED || index == BUTTON_CHROMATIC_UNFIXED;
}

void update_layout_buttons()
{
  for (int i = 0; i < 2; i++) {
    if (button_layout_map[i][1] == current_layout) {
      set_pad_colour(button_layout_map[i][0],red);
    } else {
      set_pad_colour(button_layout_map[i][0],white);
    }
  }
}

void lh_init(Layout layout)
{
  lh_set_layout(layout);
}

void lh_handle_index(int index)
{
  if (!is_in_layout_section(index)) {
    return;
  }

  switch (index) {
    case BUTTON_CHROMATIC_UNFIXED:
      current_layout = LayoutChromatic;
    break;
    case BUTTON_CHROMATIC_FIXED:
      current_layout = LayoutChromaticFixed;
    break;
    default:
    break;
  }

  update_layout_buttons();
}

Layout lh_get_layout()
{
  return current_layout;
}

void lh_set_layout(Layout layout)
{
  current_layout = layout;
  update_layout_buttons();
}
