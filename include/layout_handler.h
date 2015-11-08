#ifndef LAYOUT_HANDLER_H
#define LAYOUT_HANDLER_H

#include "layout.h"

void lh_init(Layout layout);

void lh_handle_index(int index);

Layout lh_get_layout();
void lh_set_layout(Layout layout);

#endif
