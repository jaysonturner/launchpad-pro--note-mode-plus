#ifndef GRID_H
#define GRID_H

#include "app_defs.h"

#define XY_IN_GRID(x,y) (y * 8 + x)

u8 index_to_grid(u8 index);
u8 grid_to_index(u8 grid_index);

#endif
