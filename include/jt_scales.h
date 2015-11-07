#ifndef JT_SCALES_H
#define JT_SCALES_H

#include "app_defs.h"

void jt_init();
void jt_handle_pad_event(u8 index, u8 value);
void jt_handle_midi_event(u8 index, u8 value);

#endif
