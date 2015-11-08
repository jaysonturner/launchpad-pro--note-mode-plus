#ifndef SCALE_FACTORY_H
#define SCALE_FACTORY_H

#include "app_defs.h"
#include "bool.h"

typedef enum _KeyType {
  KeyTypeMajor,
  KeyTypeMinor
}KeyType;

typedef enum _KeySignature {
  KeySignatureC,
  KeySignatureG,
  KeySignatureD,
  KeySignatureA,
  KeySignatureE,
  KeySignatureB,
  KeySignatureF,
  KeySignatureBb,
  KeySignatureEb,
  KeySignatureAb,
  KeySignatureDb,
  KeySignatureGb
}KeySignature;

typedef enum _Layout {
  LayoutChromatic,
  LayoutInKey
}Layout;

typedef struct _Note {
  u8 midi_number;
  s8 octave;
  char note;
  bool is_tonic;
  bool is_sharp;
}Note;

Note* layout_for_key_signature(u8 key, u8 type, u8 octave, Layout layout_style);

#endif
