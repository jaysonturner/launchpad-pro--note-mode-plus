#ifndef SCALE_FACTORY_H
#define SCALE_FACTORY_H

#include "app_defs.h"
#include "bool.h"
#include "layout.h"
#include "scale_type.h"

typedef enum _KeyType {
  KeyTypeMajor,
  KeyTypeMinor
}KeyType;

typedef struct _Note {
  u8 midi_number;
  s8 octave;
  char note;
  bool is_tonic;
  bool is_sharp;
  bool is_fixed_tonic;
}Note;

Note* layout_for_key_signature(u8 key, ScaleType scale_type, u8 octave, Layout layout_style);

#endif
