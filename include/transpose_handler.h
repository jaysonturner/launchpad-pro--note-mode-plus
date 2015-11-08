#ifndef TRANSPOSE_HANDLER_H
#define TRANSPOSE_HANDLER_H

void th_handle_index(int index);

void th_set_octave(int octave);
void th_set_is_minor(int minor);
void th_set_key_signature(int key_signature);

int th_get_octave();
int th_get_is_minor();
int th_get_key_signature();

#endif
