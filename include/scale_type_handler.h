#ifndef SCALE_TYPE_HANDLER_H
#define SCALE_TYPE_HANDLER_H

#include "scale_type.h"

void sth_init();
void sth_handle_index(int index);
ScaleType sth_get_selected_scale_type();
void sth_set_selected_scale_type(ScaleType scale_type);

#endif
