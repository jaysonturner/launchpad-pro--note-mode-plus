#ifndef SCALE_FACTORY_H
#define SCALE_FACTORY_H

#include "app_defs.h"

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

#endif
