#ifndef VGA_H
#define VGA_H

#include <kernel/types.h>

#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

//For VGA, we dont need anything more since we give instruction to the hardware to print via memory, so we just have functions

void my_putc(my_uchar character, my_ushort color);
void my_putstr(const my_uchar* str, my_ushort color);
void clrscr(my_uchar character, my_ushort color);

#endif