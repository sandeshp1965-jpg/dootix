#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <kernel/types.h>

#define KEYBOARD_BUFFER_SIZE 256

extern volatile my_char keyboard_buffer [KEYBOARD_BUFFER_SIZE];
extern volatile int keyboard_buffer_index;

void keyboard_handler(void);

#endif
