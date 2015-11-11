#include "scale_type_handler.h"

ScaleType current_scale_type = ScaleTypeMajor;

void sth_init()
{
  current_scale_type = ScaleTypeMajor;
}

void sth_handle_index(int index)
{

}

ScaleType sth_get_selected_scale_type()
{
  return current_scale_type;
}

void sth_set_selected_scale_type(ScaleType scale_type)
{
  current_scale_type = scale_type;
}
