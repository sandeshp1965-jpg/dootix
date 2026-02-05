#include "keyboard.h"
#include <arch/io.h>

#define KEYBOARD_BUFFER_SIZE 256

volatile my_char keyboard_buffer [KEYBOARD_BUFFER_SIZE];
volatile my_int keyboard_buffer_index = 0;

void keyboard_handler(void){
    my_char scancode = inb(0x60);
    keyboard_buffer[keyboard_buffer_index++] = scancode;

    if(keyboard_buffer_index >= KEYBOARD_BUFFER_SIZE){
        keyboard_buffer_index = 0;
    }
}